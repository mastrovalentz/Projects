#include "AnalysisUtilities/Utilities.h"
#include <math.h>

// compute energy from momentum x,y,z components and invariant mass

double Utilities::energy (double px, double py, double pz, double m) 
{
    return sqrt(pow(px,2)+pow(py,2)+pow(pz,2)+pow(m,2));
} 

// compute invariant mass from momentum x,y,z components and energy
double Utilities::inv_mass (double px, double py, double pz, double e) 
{
    return sqrt(pow(e,2)-pow(px,2)-pow(py,2)-pow(pz,2));
} 
