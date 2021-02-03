#include "stdafx.h"
#include "myUtil.h"

int MyUtil::IsCollision(RECT rc, RECT rc2)
{
	int lastSpace = 0;
	RECT up;
	RECT down;
	RECT left;
	RECT right;

	up.left = rc2.left;
	up.right = rc2.right;
	up.bottom = rc2.top;
	up.top = rc2.top - 100;

	down.left = rc2.left;
	down.right = rc2.right;
	down.top = rc2.bottom;
	down.bottom = rc2.bottom + 100;

	left.top = rc2.top;
	left.bottom = rc2.bottom;
	left.right = rc2.left;
	left.left = rc2.left - 100;

	right.top = rc2.top;
	right.bottom = rc2.bottom;
	right.left = rc2.right;
	right.right = rc2.right + 100;

	RECT temp;

	if (IntersectRect(&temp, &rc, &left) && !IntersectRect(&temp, &rc, &rc2))
	{
		lastSpace = 1;
	}
	if (IntersectRect(&temp, &rc, &right) && !IntersectRect(&temp, &rc, &rc2))
	{
		lastSpace = 2;
	}
	if (IntersectRect(&temp, &rc, &up) && !IntersectRect(&temp, &rc, &rc2))
	{
		lastSpace = 3;
	}
	if (IntersectRect(&temp, &rc, &down) && !IntersectRect(&temp, &rc, &rc2))
	{
		lastSpace = 4;
	}



	if (rc.left < rc2.left &&
		rc.right >= rc2.left &&
		rc.top < rc2.bottom &&
		rc.bottom > rc2.top)   // 왼쪽
	{
		if (lastSpace == 1)
		{
			return 1;
		}

	}
	if (rc.left <= rc2.right &&
		rc.right > rc2.right &&
		rc.top < rc2.bottom &&
		rc.bottom > rc2.top)  // 오른쪽
	{
		if (lastSpace == 2)
		{
			return 2;
		}

	}
	if (rc.left < rc2.right &&
		rc.right > rc2.left &&
		rc.top < rc2.top &&
		rc.bottom >= rc2.top)  // 위
	{
		if (lastSpace == 3)
		{
			return 3;
		}

	}
	if (rc.left < rc2.right &&
		rc.right > rc2.left &&
		rc.top <= rc2.bottom &&
		rc.bottom > rc2.bottom)  // 아래
	{
		if (lastSpace == 4)
		{
			return 4;
		}

	}
	return 0;
}

int MyUtil::IsCollisionNonEqual(RECT rc, RECT rc2)
{
	int lastSpace = 0;
	RECT up;
	RECT down;
	RECT left;
	RECT right;

	up.left = rc2.left;
	up.right = rc2.right;
	up.bottom = rc2.top;
	up.top = rc2.top - 100;

	down.left = rc2.left;
	down.right = rc2.right;
	down.top = rc2.bottom;
	down.bottom = rc2.bottom + 100;

	left.top = rc2.top;
	left.bottom = rc2.bottom;
	left.right = rc2.left;
	left.left = rc2.left - 100;

	right.top = rc2.top;
	right.bottom = rc2.bottom;
	right.left = rc2.right;
	right.right = rc2.right + 100;

	RECT temp;

	if (IntersectRect(&temp, &rc, &left) && !IntersectRect(&temp, &rc, &rc2))
	{
		lastSpace = 1;
	}
	if (IntersectRect(&temp, &rc, &right) && !IntersectRect(&temp, &rc, &rc2))
	{
		lastSpace = 2;
	}
	if (IntersectRect(&temp, &rc, &up) && !IntersectRect(&temp, &rc, &rc2))
	{
		lastSpace = 3;
	}
	if (IntersectRect(&temp, &rc, &down) && !IntersectRect(&temp, &rc, &rc2))
	{
		lastSpace = 4;
	}


	if (rc.left < rc2.left &&
		rc.right > rc2.left &&
		rc.top < rc2.bottom &&
		rc.bottom > rc2.top)   // 왼쪽
	{
		if (lastSpace == 1)
		{
			return 1;
		}

	}
	if (rc.left < rc2.right &&
		rc.right > rc2.right &&
		rc.top < rc2.bottom &&
		rc.bottom > rc2.top)  // 오른쪽
	{
		if (lastSpace == 2)
		{
			return 2;
		}

	}
	if (rc.left < rc2.right &&
		rc.right > rc2.left &&
		rc.top < rc2.top &&
		rc.bottom > rc2.top)  // 위
	{
		if (lastSpace == 3)
		{
			return 3;
		}

	}
	if (rc.left < rc2.right &&
		rc.right > rc2.left &&
		rc.top < rc2.bottom &&
		rc.bottom > rc2.bottom)  // 아래
	{
		if (lastSpace == 4)
		{
			return 4;
		}

	}
	return 0;
}
