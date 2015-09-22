//
//  instances.cpp
//  tinyxml2
//
//  Created by Yun HE on 22/09/2015.
//
//

#include <stdio.h>
#include <string>
namespace input
{
    class instances
    {


        /// <summary>The name of the instance. </summary>
        ///
        std::string name;


        /// <summary>The duration of timesteps. This granularity is
        /// the one of production/consumption forecasts. </summary>
        ///
        int unit;

        /// <summary>The horizon (constant H in the mathematical model)
        /// gives the duration of the considered prevision period.
        ///
        /// All time-related inputs will be defined as Point within
        /// interval [0,horizon*unit[.</summary>
        ///
        int horizon;


        /// <summary>DISTMATRIX(p,q) is the distance between
        /// Index p and q .</summary>
        ///
        double * * DistMatrices;

        /// <summary>TIMEMATRIX(p,q) is the travelling time
        /// from p to q.</summary>
        ///
        int timeMatrices;


        /// <summary>The list of drivers. </summary>
        ///
        //driver* drivers;

/// <summary>The list of trailers.</summary>
///
//public IRP_Roadef_Challenge_Instance_Trailers[] trailers;

/// <summary>The list of bases.</summary>
///
//public IRP_Roadef_Challenge_Instance_Bases bases;

/// <summary>The list of sources.</summary>
///
//public IRP_Roadef_Challenge_Instance_Sources[] sources;

/// <summary>The list of customers.</summary>
///
//public IRP_Roadef_Challenge_Instance_Customers[] customers;



instances()
{
    
}


/// <summary>Return the first minute outside of the schedule that is to say : (Horizon+1)*Unit.</summary>
///
/// <returns>The last Minute of the shedule</returns>
///
int getLatestTime()
{
    return ( horizon + 1 ) * unit;
}


};


}