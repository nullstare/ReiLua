#pragma once

/* Linear Easing functions. */
int leasingsEaseLinear( lua_State *L );

/* Sine Easing functions. */
int leasingsEaseSineIn( lua_State *L );
int leasingsEaseSineOut( lua_State *L );
int leasingsEaseSineInOut( lua_State *L );

/* Circular Easing functions. */
int leasingsEaseCircIn( lua_State *L );
int leasingsEaseCircOut( lua_State *L );
int leasingsEaseCircInOut( lua_State *L );

/* Cubic Easing functions. */
int leasingsEaseCubicIn( lua_State *L );
int leasingsEaseCubicOut( lua_State *L );
int leasingsEaseCubicInOut( lua_State *L );

/* Quadratic Easing functions. */
int leasingsEaseQuadIn( lua_State *L );
int leasingsEaseQuadOut( lua_State *L );
int leasingsEaseQuadInOut( lua_State *L );

/* Exponential Easing functions. */
int leasingsEaseExpoIn( lua_State *L );
int leasingsEaseExpoOut( lua_State *L );
int leasingsEaseExpoInOut( lua_State *L );

/* Back Easing functions. */
int leasingsEaseBackIn( lua_State *L );
int leasingsEaseBackOut( lua_State *L );
int leasingsEaseBackInOut( lua_State *L );

/* Bounce Easing functions. */
int leasingsEaseBounceIn( lua_State *L );
int leasingsEaseBounceOut( lua_State *L );
int leasingsEaseBounceInOut( lua_State *L );

/* Elastic Easing functions. */
int leasingsEaseElasticIn( lua_State *L );
int leasingsEaseElasticOut( lua_State *L );
int leasingsEaseElasticInOut( lua_State *L );
