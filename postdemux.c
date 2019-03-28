#include <libavformat/avformat.h>
#include <time.h>
#include <limits.h>
#include "postdemux.h"

#include "log.h"

static const int64_t MAX_PTS = 8589934592;

static void postdemux_update_packet(struct postdemux_ctx *ctx, AVPacket *pkt)
{
    pkt->pts = ctx->count * ctx->frame_period;
    ctx->count += 1;
}

struct postdemux_ctx *sxpi_postdemux_alloc(void *log_ctx, int32_t time_base_num, int32_t time_base_den, int32_t framerate_frames, int32_t framerate_secs)
{
    struct postdemux_ctx *ctx = av_mallocz(sizeof(*ctx));
    if (!ctx)
        return NULL;
    
    ctx->log_ctx = log_ctx;
    ctx->update_packet = &postdemux_update_packet;
    ctx->offset = -1;
    ctx->count = 0;
    ctx->time_base_num = time_base_num;
    ctx->time_base_den = time_base_den;
    ctx->framerate_frames = framerate_frames;
    ctx->framerate_secs = framerate_secs;
    ctx->frame_period = (framerate_secs * time_base_den) / (framerate_frames * time_base_num);
    LOG(ctx, ERROR, "tn/td/frf/frs/fper,%d,%d,%d,%d,%d",
        time_base_num, time_base_den, framerate_frames, framerate_secs, ctx->frame_period);
    return ctx;
}
