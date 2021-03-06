#ifndef __CORE_MACROS_H__
#define __CORE_MACROS_H__

#ifdef _DEBUG
#define FORCE_INLINE
#else
#define FORCE_INLINE	__forceinline
#endif

#define ALIGN(x) __declspec(align(n))

#define SAFE_DELETE( X ) if( X != NULL )\
{\
	delete X;\
	X = NULL;\
}
#define SAFE_DELETE_ARRAY( X ) if( X != NULL )\
{\
	delete[] X;\
	X = NULL;\
}

#define SAFE_RELEASE( X ) if( X != NULL )\
{\
	X->Release();\
	X = NULL;\
}


//-----------------------------
// bitFields
//-----------------------------

#define ISBITSET( bitField , bit )	( bitField & ( 1 << bit ) ) 
#define SETBIT( bitField , bit ) bitField |= ( 1 << bit )
#define CLEARBIT ( bitField , bit ) bitField &= ~( 1 << bit )
#define TOOGLEBIT ( bitField , mask ) bitField ^= ( 1 << bit )

#define ISMASKSET( bitField , mask ) return ( bitField & mask ) 
#define SETMASK( bitField , mask ) bitField |= mask
#define CLEARMASK ( bitField , mask ) bitField &= ~mask
#define TOOGLEMASK ( bitField , mask ) bitField ^= mask


#endif