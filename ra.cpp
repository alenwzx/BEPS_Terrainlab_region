/*************************************************************************

 	Output air resistance/conductance.

*****************************************************************************/

#include "stdafx.h"
#include "BepsHydrScience.h"
#include <math.h>

void ra(double *b,double *g,double *x,double *z)
//  double b[],g[],x[],z[];
{
	/* input */
	double u	=z[44];		/* wind speed at height z */
	double zz	=25;//15;	/* height (MEM: REFERENCE HEIGHT!!!) (m) */
	double h	=10;//10;	/* tree height (m) */
	double radg	=600;//500 	/* total radiation W/m2 */
	double T	=20;	/* air temperature (C) */
	double lw	=0.4;//0.3	/* leaf charcteristic width =0.3 for BS*/
	double sigma=5;		/* shelter factor =5 for BS */
	double lai	=4.5;//z[10];//3.56;		/* leaf area index */
	double omega=0.5;	/* cluming index */

	/* constants */
	double k;			/* von Karman's constant */
	double beta;		/* Bowen's ratio	*/
	double cp;			/* specific heat of air (J/kg/K) */
	double rho;			/* density of air (kg/m3)*/
	double gg;			/* gravitational acceleration (m/s2) */
	double n;
	double nu_lower;	/* viscosity (cm2/s) (MEM: air!!; WHY not using m2/s? )  */

	/* intermediate output */
	double d;			/* displacement height (m) */
	double z0;			/* roughness length (m) */
	double ustar;		/* friction velocity (m/s) */
	double QH;			/* heat flux */
	double L;
	double Le;

	double uh;			/* wind speed at height h */
	double ud;			/* wind speed at height d */
	double gamma;
	double Re;			/* Reynold's number */
	double Nu;			/* Nusselt number */
	double alfac;
	double alfaw;

	/* final output */
	double ram;
	double rac;
	double ra;

	k			= 0.4;
	beta		= 0.5;
	cp			= 1010;
	rho			= 1.225;	/* at 15 C */
	gg			= 9.8;
	n			= 5.0;
	nu_lower	= 0.15;
	alfac		= 0.15;		/* for CO2 */
	alfaw		= 0.25;		/* for H2O */

	/********* Surface layer aerodynamic resisistance ****************/

	d	= 0.7*h;
	z0	= 0.1*h;

	ustar = u*k/log((zz-d)/z0);

	QH = beta*radg;
	L  = - (rho*cp*T*pow(ustar,3))/(k*gg*QH);


	ram = 1/(k*ustar)*(log((zz-d)/z0));

	/********* Leaf boundary layer resistance ******************/

	/* Wind speed at the top of the canopy */
	uh = 1.1*ustar*k;

	Le = lai*omega;

	gamma = (0.167+0.179*uh)*pow(Le, 1/3);

	/* Wind speed at d, taking as the mean wind speed inside a stand */
	ud = uh*exp(-0.3*gamma);

	/* Reynold's number */
	Re = (ud*lw/sigma)/nu_lower;

	/* Nusselt number */
	Nu = 0.62*pow(Re,0.47);

	/* leaf boundary resistance */
	rac = lw/(alfac*Nu);

	/********* Total air resistance ******************/

	ra = ram+rac/lai;              //总空气阻抗

	/* Total air conductance */    //总空气导度
	g[40]= (1/ra)*0.50;

//Tague and Band,2004_________________________________________________
	double ra_0;
	double ra_u;
	double ra_floor;
	float cn=2.78; //corn it is 3 then why not 5 for an Open Black Spruce?
	int h2=2; //understorey height
	float h3=0.1;//moss height
	float d2=0.7*h2;
	float z0_2=0.1*h2;
	double termA;
	double termB;
	double termC;
	double termD;
	double termE;
	double ustar_2;
	//double ustar_3;
ustar_2= ustar*(log((h2-d2)/(z0_2))/log((3-d2)/h2));
//ustar_3=ustar_2*(log((h2*1.5-d2)/(h2))/log((zz-d)/h));
termA= log((zz-d)/z0);
ra_0 =(termA/(0.41*0.41))/ustar;
termB=exp(-1*(cn*((h2+d2)/z0)));
termC=exp(-1*(cn*((h+d)/z0)));
termD=ustar_2*0.41*0.41*cn*(z0-d);
termE=(log((0.1*h2*0.1*h2)/(h3)))/(0.41*0.41*ustar_2);
ra_u=ra_0+(termA*exp(-1*cn)*((termB-termC)/termD));
ra_floor=ra_u+termE;
//new aerodyamic conductances derived from resistances (1/x) stored in g[70-72];
g[70]=1/ra_0;
g[71]=1/ra_u;
g[72]=1/ra_floor;
//_______________________________end Tague model_________________________________


 }

