#ifndef LCAM_LIB_H__
#define LCAM_LIB_H__

#include <lua.h>
#include <lauxlib.h>

#ifdef __cplusplus
extern "C" {
#endif

LUALIB_API int luaopen_lcam(lua_State *L);

#ifdef __cplusplus
}
#endif
#endif /* LCAM_LIB_H__ */
