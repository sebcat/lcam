#include "lcam-lib.h"
#include "lcam.h"

#define LCAM_CAMERA_PROVIDER "lcam_camera_provider"
/*
static inline struct lcam_provider *tolcam_provider(lua_State *L, int arg)
{
    return *(struct lcam_provider **)luaL_checkudata(L, arg, LCAM_CAMERA_PROVIDER);
}
*/
static int lcam_get_service(lua_State *L)
{
    int ret;
    int nargs;
    const char *service_name = NULL;

    nargs = lua_gettop(L);
    if (nargs == 1) {
        service_name = luaL_checkstring(L, 1);
    }

    struct lcam_provider **a = lua_newuserdata(L, sizeof(struct lcam_provider*));
    luaL_setmetatable(L, LCAM_CAMERA_PROVIDER);
    *a = lcam_provider_new();
    if (!*a) {
        return luaL_error(L, "failed to allocate camera provider");
    }

    ret = lcam_provider_init(*a, service_name);
    if (ret != 0) {
        return luaL_error(L, "%s", lcam_provider_strerror(*a));
    }

    return 1;
}

static const luaL_Reg lcamprovider[] = {
    {},
};

static const luaL_Reg lcamlib[] = {
    {"get_service", lcam_get_service},
    {},
};

LUALIB_API int luaopen_lcam(lua_State *L)
{
    luaL_newmetatable(L, LCAM_CAMERA_PROVIDER);
    luaL_setfuncs(L, lcamprovider, 0);
    lua_pushvalue(L, -1);
    lua_setfield(L, -1, "__index");

    lua_newtable(L);
    luaL_setfuncs(L, lcamlib, 0);
    return 1;
}
