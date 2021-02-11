#include <DxLib.h>
#include <math.h>
#include <time.h>

#define PI atan(1.0) * 4.0

int Shake(int *x, int *y, double *power, int *shakeTime, const int &area, bool reset = FALSE)
{
	static int t;

	if (reset == TRUE)
	{
		t = *shakeTime;
		*x = 0;
		*y = 0;
	}

	if (x != nullptr && y != nullptr && power != nullptr && shakeTime != nullptr)
	{
		int a = area * (*power);

		if (*shakeTime > 0)
		{
			*x = GetRand(a) - a / 2;
			*y = GetRand(a) - a / 2;
			*power -= sin(PI * 2.0 / (*shakeTime * 4.0) * (*shakeTime + (double)t)) * 2.0;
			*shakeTime -= 1;
		}
	}

	return t;
}