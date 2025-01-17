#include "main.h"
#include "state.h"
#include "lua_core.h"
#include "core.h"
#include "bitwiseOp.h"

/*
## Bitwise Operations - Arithmetic
*/

/*
> result = RL.BitAnd( int a, int b )

Equivalent to a & b in C

- Success return int
*/
int lbitAnd( lua_State* L ) {
	uint64_t a = luaL_checkinteger( L, 1 );
	uint64_t b = luaL_checkinteger( L, 2 );

	lua_pushinteger( L, a & b );

	return 1;
}

/*
> result = RL.BitOr( int a, int b )

Equivalent to a | b in C

- Success return int
*/
int lbitOr( lua_State* L ) {
	uint64_t a = luaL_checkinteger( L, 1 );
	uint64_t b = luaL_checkinteger( L, 2 );

	lua_pushinteger( L, a | b );

	return 1;
}

/*
> result = RL.BitXor( int a, int b )

Equivalent to a ^ b in C

- Success return int
*/
int lbitXor( lua_State* L ) {
	uint64_t a = luaL_checkinteger( L, 1 );
	uint64_t b = luaL_checkinteger( L, 2 );

	lua_pushinteger( L, a ^ b );

	return 1;
}

/*
> result = RL.BitNot( int v )

Equivalent to ~v in C

- Success return int
*/
int lbitNot( lua_State* L ) {
	uint64_t v = luaL_checkinteger( L, 1 );

	lua_pushinteger( L, ~v );

	return 1;
}

/*
> result = RL.BitShiftLeft( int v, int n )

Equivalent to v << n in C

- Success return int
*/
int lbitShiftLeft( lua_State* L ) {
	uint64_t v = luaL_checkinteger( L, 1 );
	uint64_t n = luaL_checkinteger( L, 2 );

	lua_pushinteger( L, v << n );

	return 1;
}

/*
> result = RL.BitShiftRight( int v, int n )

Equivalent to v >> n in C

- Success return int
*/
int lbitShiftRight( lua_State* L ) {
	uint64_t v = luaL_checkinteger( L, 1 );
	uint64_t n = luaL_checkinteger( L, 2 );

	lua_pushinteger( L, v >> n );

	return 1;
}

/*
> result = RL.BitSet( int v, int i, bool b )

Set bit in index i to state b in value v

- Success return int
*/
int lbitSet( lua_State* L ) {
	uint64_t v = luaL_checkinteger( L, 1 );
	uint64_t i = luaL_checkinteger( L, 2 );
	bool b = uluaGetBoolean( L, 3 );

	lua_pushinteger( L, b ? v | 1UL << i : v & ~( 1UL << i ) );

	return 1;
}

/*
> bit = RL.BitGet( int v, int i )

Get bit in index i from value v

- Success return bool
*/
int lbitGet( lua_State* L ) {
	uint64_t v = luaL_checkinteger( L, 1 );
	uint64_t i = luaL_checkinteger( L, 2 );

	lua_pushboolean( L, 0UL < ( v & ( 1UL << i ) ) );

	return 1;
}

/*
> result = RL.BitToggle( int v, int i )

Toggle bit in index i in value v

- Success return int
*/
int lbitToggle( lua_State* L ) {
	uint64_t v = luaL_checkinteger( L, 1 );
	uint64_t i = luaL_checkinteger( L, 2 );

	lua_pushinteger( L, v ^ 1UL << i );

	return 1;
}
