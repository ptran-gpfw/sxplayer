#include <libavformat/avformat.h>
#include <time.h>
#include <limits.h>
#include "postdemux.h"

#include "log.h"

static const int64_t MAX_PTS = 8589934592;

static void postdemux_update_packet(struct postdemux_ctx *ctx, AVPacket *pkt)
{
    pkt->pts /= 2;
}

struct postdemux_ctx *sxpi_postdemux_alloc(void *log_ctx, AVStream *avstream)
{
    struct postdemux_ctx *ctx = av_mallocz(sizeof(*ctx));
    if (!ctx)
        return NULL;
    
    ctx->log_ctx = log_ctx;
    ctx->update_packet = &postdemux_update_packet;
    ctx->offset = -1;
    ctx->avstream = avstream;
    return ctx;
}
