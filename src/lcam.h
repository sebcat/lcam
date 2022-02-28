#ifndef ANDROID_LCAM_H__
#define ANDROID_LCAM_H__

#ifdef __cplusplus
extern "C" {
#endif

struct lcam_provider;

struct lcam_provider *lcam_provider_new(void);
void lcam_provider_free(struct lcam_provider *p);
const char *lcam_provider_strerror(struct lcam_provider *p);
int lcam_provider_init(struct lcam_provider *p, const char *service_name);

#ifdef __cplusplus
}
#endif
#endif /* ANDROID_LCAM_H__ */
