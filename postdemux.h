/*
 * This file is part of sxplayer.
 *
 * Copyright (c) 2019 GoPro
 *
 * sxplayer is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * sxplayer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with sxplayer; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef MOD_POSTDEMUX_H
#define MOD_POSTDEMUX_H

#include <libavformat/avformat.h>

struct postdemux_ctx {
    void *log_ctx;
    void (*update_packet)(struct postdemux_ctx *, AVPacket *);
    int64_t offset;
    int64_t count;
    int32_t time_base_num;
    int32_t time_base_den;
    int32_t framerate_frames;
    int32_t framerate_secs;
    int32_t frame_period;
};

struct postdemux_ctx *sxpi_postdemux_alloc(void *log_ctx, int32_t time_base_num, int32_t time_base_den, int32_t framerate_frames, int32_t framerate_secs);

#endif
