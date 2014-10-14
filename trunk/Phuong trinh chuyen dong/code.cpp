//
//int move_x_1 = 0;
//int speedX= 1;
//int speedY = 1;
//float angle_1 = 0;
//float scale = 0.1f;
//int flag = 1;
//float _x_1 = 100;
//float _y_1 = 300;
//float _x2 = 200;
//float _y2 = 300;
//float _x3 = 0;
//float _y3 = 100;
//float _x_j = 400;
//float _y_j = 0;
//void Rotate(float &x, float &y, float angle)
//{
//	if(move_x_1 >= 750 || move_x_1 < 0 )
//		speedX *= -1;
//	move_x_1 += 3*speedX;
//	x = move_x_1 + 40 * cos(angle);
//	//x = hoanh do tam xoay + ban kinh * cos(goc xoay)
//	y = 300 + 40 * sin(angle);
//	//y = tung do tam xoay + ban kinh * sin(goc xoay)
//	
//}
//
//void Diagonal(float &x, float &y)
//{
//	y = x + 5;
//	x += 2*speedX;
//}
//
//void Sin(float &x, float &y)
//{
//	y = sin(x * 3.14 / 180.0) * 50 + 200;
//	if(x >= 800)
//		speedX *= -1;
//	x += 2*speedX;
//}
//
//void Scale(float &s)
//{
//	if(s == 1.0f || s == 2.0f)
//		flag *= -1;
//	s = s + (flag * 0.01f);
//}
//
//void Jump(float &x, float &y)
//{
//	x = 100;
//	if(y > 600 || y < 0)
//		speedY *= -1;
//	y += 2*speedY;
//	
//}
//	
void Rotate(float &x, float &y, float angle)
{
	if(move_x_1 >= 750 || move_x_1 < 0 )
		speedX *= -1;
	move_x_1 += 3*speedX;
	x = move_x_1 + 40 * cos(angle);
	//x = hoanh do tam xoay + ban kinh * cos(goc xoay)
	y = 300 + 40 * sin(angle);
	//y = tung do tam xoay + ban kinh * sin(goc xoay)
	
}

void Diagonal(float &x, float &y)
{
	y = x + 5;
	x += 2*speedX;
}

void Sin(float &x, float &y)
{
	y = sin(x * 3.14 / 180.0) * 50 + 200;
	if(x >= 800)
		speedX *= -1;
	x += 2*speedX;
}

void Scale(float &s)
{
	if(s == 1.0f || s == 2.0f)
		flag *= -1;
	s = s + (flag * 0.01f);
}

void Jump(float &x, float &y)
{
	x = 100;
	if(y > 600 || y < 0)
		speedY *= -1;
	y += 2*speedY;
	
}