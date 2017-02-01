
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <sys/timeb.h>
#include <time.h>


/*
** Robot functions
*/



/* This robot moves randomly */

void RandomRobot(int FoodClosestDistance,	/* input - closest food in pixels */
				 int FoodClosestAngle,		/* input - angle in degrees towards closest food */
				 int RobotClosestDistance,	/* input - closest other robot, in pixels */
				 int RobotClosestAngle,		/* input - angle in degrees towards closest robot */
				 int SharkClosestDistance,	/* input - closest shark in pixels */
				 int SharkClosestAngle,		/* input - angle in degrees towards closest shark */
				 int CurrentRobotEnergy,		/* input - this robot's current energy (50 - 255) */
				 int *RobotMoveAngle,		/* output - angle in degrees to move */
				 int *RobotExpendEnergy)		/* output - energy to expend in motion (cannot exceed Current-50) */

{
	(*RobotMoveAngle)=(rand() % 360);
	if (CurrentRobotEnergy > 50)
		(*RobotExpendEnergy)=(rand() % (CurrentRobotEnergy-50));
	else
		(*RobotExpendEnergy)=1;
	if ((*RobotExpendEnergy) > 10)
		(*RobotExpendEnergy)=10;
}



/* This robot moves towards food, ignoring sharks */

void GreedyRobot(int FoodClosestDistance,	/* input - closest food in pixels */
				 int FoodClosestAngle,		/* input - angle in degrees towards closest food */
				 int RobotClosestDistance,	/* input - closest other robot, in pixels */
				 int RobotClosestAngle,		/* input - angle in degrees towards closest robot */
				 int SharkClosestDistance,	/* input - closest shark in pixels */
				 int SharkClosestAngle,		/* input - angle in degrees towards closest shark */
				 int CurrentRobotEnergy,		/* input - this robot's current energy (50 - 255) */
				 int *RobotMoveAngle,		/* output - angle in degrees to move */
				 int *RobotExpendEnergy)		/* output - energy to expend in motion (cannot exceed Current-50) */

{
	(*RobotMoveAngle)=FoodClosestAngle;
	(*RobotExpendEnergy)=30;
}


/* This robot moves away from sharks, ignoring food */

void ScaredRobot(int FoodClosestDistance,	/* input - closest food in pixels */
				 int FoodClosestAngle,		/* input - angle in degrees towards closest food */
				 int RobotClosestDistance,	/* input - closest other robot, in pixels */
				 int RobotClosestAngle,		/* input - angle in degrees towards closest robot */
				 int SharkClosestDistance,	/* input - closest shark in pixels */
				 int SharkClosestAngle,		/* input - angle in degrees towards closest shark */
				 int CurrentRobotEnergy,		/* input - this robot's current energy (50 - 255) */
				 int *RobotMoveAngle,		/* output - angle in degrees to move */
				 int *RobotExpendEnergy)		/* output - energy to expend in motion (cannot exceed Current-50) */

{
	(*RobotMoveAngle)=(180+SharkClosestAngle)%360;
	if (SharkClosestDistance < 30)
		(*RobotExpendEnergy)=30;
	else
		(*RobotExpendEnergy)=30-SharkClosestDistance/10;
	if ((*RobotExpendEnergy) < 3)
		(*RobotExpendEnergy)=3;
}
void two(int FoodClosestDistance,	/* input - closest food in pixels */
		 int FoodClosestAngle,		/* input - angle in degrees towards closest food */
		 int RobotClosestDistance,	/* input - closest other robot, in pixels */
		 int RobotClosestAngle,		/* input - angle in degrees towards closest robot */
		 int SharkClosestDistance,	/* input - closest shark in pixels */
		 int SharkClosestAngle,		/* input - angle in degrees towards closest shark */
		 int CurrentRobotEnergy,		/* input - this robot's current energy (50 - 255) */
		 int *RobotMoveAngle,		/* output - angle in degrees to move */
		 int *RobotExpendEnergy)		/* output - energy to expend in motion (cannot exceed Current-50) */

{
	static int scd,sca,fca,fcd,rca,rcd;

	if(CurrentRobotEnergy>=150 )
	{
		if((FoodClosestDistance<SharkClosestDistance &&FoodClosestDistance<=15))
		{
			(*RobotMoveAngle)=FoodClosestAngle;
			(*RobotExpendEnergy)=FoodClosestDistance;
		}
		else if(SharkClosestDistance<FoodClosestDistance)
		{
			if(SharkClosestDistance<15)
			{
				if(sca-15<SharkClosestAngle &&sca+15>SharkClosestAngle)
				{
					if(scd>SharkClosestDistance)
					{
						(*RobotMoveAngle)=(45+SharkClosestAngle)%360;
						(*RobotExpendEnergy)=10-SharkClosestDistance/10;
					}
				}
				else
				{
					(*RobotMoveAngle)=(135+SharkClosestAngle)%360;
					if (SharkClosestDistance < 10)
						(*RobotExpendEnergy)=10;
					else
						(*RobotExpendEnergy)=20-SharkClosestDistance/10;
				}
			}
			else
			{
				(*RobotMoveAngle)=(180+SharkClosestAngle)%360;
				(*RobotExpendEnergy)=20-SharkClosestDistance/10;
			}

		}
	}

	else if (CurrentRobotEnergy<150 &&  CurrentRobotEnergy>80)
	{
		if((FoodClosestAngle!=SharkClosestAngle)&&(FoodClosestDistance<SharkClosestDistance))
		{
			(*RobotMoveAngle)=FoodClosestAngle;
			(*RobotExpendEnergy)=FoodClosestDistance;
		}
		else
		{
			if(sca-15<SharkClosestAngle &&sca+15>SharkClosestAngle)
			{
				if(scd>SharkClosestDistance)
				{
					(*RobotMoveAngle)=(45+SharkClosestAngle)%360;
					(*RobotExpendEnergy)=10-SharkClosestDistance/10;
				}
			}
			else
			{
				(*RobotMoveAngle)=(135+SharkClosestAngle)%360;
				if (SharkClosestDistance < 10)
					(*RobotExpendEnergy)=10;
				else
					(*RobotExpendEnergy)=20-SharkClosestDistance/10;
			}
		}
	}
	else 
	{

		(*RobotMoveAngle)=FoodClosestAngle;
		(*RobotExpendEnergy)=FoodClosestDistance;

	}



	scd=SharkClosestDistance;
	sca=SharkClosestAngle;
	fca=FoodClosestAngle;
	fcd=FoodClosestDistance;
	rca=RobotClosestAngle;
	rcd=RobotClosestDistance;
}

void one(int FoodClosestDistance,	/* input - closest food in pixels */
		 int FoodClosestAngle,		/* input - angle in degrees towards closest food */
		 int RobotClosestDistance,	/* input - closest other robot, in pixels */
		 int RobotClosestAngle,		/* input - angle in degrees towards closest robot */
		 int SharkClosestDistance,	/* input - closest shark in pixels */
		 int SharkClosestAngle,		/* input - angle in degrees towards closest shark */
		 int CurrentRobotEnergy,		/* input - this robot's current energy (50 - 255) */
		 int *RobotMoveAngle,		/* output - angle in degrees to move */
		 int *RobotExpendEnergy)		/* output - energy to expend in motion (cannot exceed Current-50) */

{

	static int scd,sca;


	if(SharkClosestDistance>100)
	{

		if(CurrentRobotEnergy>=150 )
		{
			if((FoodClosestDistance<SharkClosestDistance))
			{
				(*RobotMoveAngle)=FoodClosestAngle;
				(*RobotExpendEnergy)=20;
			}
			else if(SharkClosestDistance<FoodClosestDistance)
			{
				if(sca==SharkClosestAngle)
				{
					if(scd>SharkClosestDistance)
					{
						(*RobotMoveAngle)=(45+SharkClosestAngle)%360;
						(*RobotExpendEnergy)=10-SharkClosestDistance/10;
					}
				}
				else
				{
					(*RobotMoveAngle)=(135+SharkClosestAngle)%360;
					if (SharkClosestDistance < 10)
						(*RobotExpendEnergy)=10;
					else
						(*RobotExpendEnergy)=20-SharkClosestDistance/10;
				}
			}
		}

		else if (CurrentRobotEnergy<150 &&  CurrentRobotEnergy>80)
		{
			if((FoodClosestAngle!=SharkClosestAngle)&&(FoodClosestDistance<SharkClosestDistance))
			{
				(*RobotMoveAngle)=FoodClosestAngle;
				(*RobotExpendEnergy)=FoodClosestDistance;
			}
			else
			{
				if(sca==SharkClosestAngle)
				{
					if(scd>SharkClosestDistance)
					{
						(*RobotMoveAngle)=(45+SharkClosestAngle)%360;
						(*RobotExpendEnergy)=10-SharkClosestDistance/10;
					}
				}
				else
				{
					(*RobotMoveAngle)=(135+SharkClosestAngle)%360;
					if (SharkClosestDistance < 10)
						(*RobotExpendEnergy)=10;
					else
						(*RobotExpendEnergy)=20-SharkClosestDistance/10;
				}
			}
		}
		else 
		{

			(*RobotMoveAngle)=FoodClosestAngle;
			(*RobotExpendEnergy)=FoodClosestDistance;

		}
	}
	else
	{
		if(CurrentRobotEnergy>125)
		{
			(*RobotMoveAngle)=(150+SharkClosestAngle)%360;
			if (SharkClosestDistance < 30)
				(*RobotExpendEnergy)=30;
			else
				(*RobotExpendEnergy)=30-SharkClosestDistance/10;
			if ((*RobotExpendEnergy) < 3)
				(*RobotExpendEnergy)=3;
		}

		else
		{

			(*RobotMoveAngle)=FoodClosestAngle;
			(*RobotExpendEnergy)=FoodClosestDistance;
		}

	}
	scd=SharkClosestDistance;
	sca=SharkClosestAngle;
}

void zero(int FoodClosestDistance,	/* input - closest food in pixels */
		  int FoodClosestAngle,		/* input - angle in degrees towards closest food */
		  int RobotClosestDistance,	/* input - closest other robot, in pixels */
		  int RobotClosestAngle,		/* input - angle in degrees towards closest robot */
		  int SharkClosestDistance,	/* input - closest shark in pixels */
		  int SharkClosestAngle,		/* input - angle in degrees towards closest shark */
		  int CurrentRobotEnergy,		/* input - this robot's current energy (50 - 255) */
		  int *RobotMoveAngle,		/* output - angle in degrees to move */
		  int *RobotExpendEnergy)		/* output - energy to expend in motion (cannot exceed Current-50) */

{

	if(CurrentRobotEnergy>=125)
	{
		if((FoodClosestDistance<SharkClosestDistance))
		{
			(*RobotMoveAngle)=FoodClosestAngle;
			(*RobotExpendEnergy)=20;
		}
		else if(SharkClosestDistance<FoodClosestDistance)
		{
			(*RobotMoveAngle)=(135+SharkClosestAngle)%360;
			if (SharkClosestDistance < 10)
				(*RobotExpendEnergy)=10;
			else
				(*RobotExpendEnergy)=20-SharkClosestDistance/10;
		}
	}
	else
	{
		if(FoodClosestAngle!=SharkClosestAngle)
		{
			(*RobotMoveAngle)=FoodClosestAngle;
			(*RobotExpendEnergy)=FoodClosestDistance;
		}
		else
		{
			(*RobotMoveAngle)=(135+SharkClosestAngle)%360;
			if (SharkClosestDistance < 10)
				(*RobotExpendEnergy)=10;
			else
				(*RobotExpendEnergy)=20-SharkClosestDistance/10;
		}
	}

}
