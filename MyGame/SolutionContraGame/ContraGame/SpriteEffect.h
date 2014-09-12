//#if !defined __SPRITE_EFFECT_H__
//#define __SPRITE_EFFECT_H__
//#include <d3dx9.h>
//#include <d3d9.h>
//
//class SpriteEffect
//{
//private:
//
//public:
//	SpriteEffect(){}
//	static void FlipHorizontally(D3DXMATRIX *matrixTrans, RECT* frameRect)
//	{
//		matrixTrans->_11 = -1;//cos(180)
//		matrixTrans->_33 = -1;//cos(180)
//		matrixTrans->_13 = 0;//-sin(180)
//		matrixTrans->_31 = 0;//sin(180)
//
//		matrixTrans->_41 = frameRect->right;
//		//matrixTrans->_42 = 33;
//	}
//	static void FlipVertically(D3DXMATRIX *matrixTrans, RECT* frameRect)
//	{
//		matrixTrans->_22 = -1;//cos(180)
//		matrixTrans->_33 = -1;//cos(180)
//		matrixTrans->_23 = 0;//-sin(180)
//		matrixTrans->_32 = 0;//sin(180)
//
//		//matrixTrans->_41 = 60;
//		matrixTrans->_42 = frameRect->bottom;
//	}
//	static void None(D3DXMATRIX *matrixTrans, RECT* frameRect)
//	{
//
//	}
//	~SpriteEffect(){}
//};
//
//#endif