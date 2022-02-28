#include <stdio.h>
#include <stdarg.h>

#include <android/hardware/camera/provider/2.6/ICameraProvider.h>

#include "lcam.h"

#define LCAM_ERRMSG_SZ 128

using android::hardware::camera::provider::V2_6::ICameraProvider;
using android::sp;

struct lcam_provider {
    sp<ICameraProvider> provider;
    char errmsg[LCAM_ERRMSG_SZ];
};

static int lcam_provider_error(struct lcam_provider *p, const char *fmt, ...)
    __attribute__ ((format (printf, 2, 3)));

int lcam_provider_error(struct lcam_provider *p, const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    vsnprintf(p->errmsg, sizeof(p->errmsg), fmt, ap);
    va_end(ap);
    return -1;
}

struct lcam_provider *lcam_provider_new(void)
{
    struct lcam_provider *p = new (std::nothrow) struct lcam_provider;
    p->errmsg[0] = '\0';
    return p;
}

void lcam_provider_free(struct lcam_provider *p)
{
    if (p) {
        delete p;
    }
}

const char *lcam_provider_strerror(struct lcam_provider *p)
{
    return p->errmsg;
}

int lcam_provider_init(struct lcam_provider *p, const char *service_name)
{
    if (service_name) {
        p->provider = ICameraProvider::getService(service_name);
    } else {
        p->provider = ICameraProvider::getService();
    }

    if (p->provider == nullptr) {
        return lcam_provider_error(p, "%s: failed to get camera provider service", __func__);
    }

    return 0;
}
