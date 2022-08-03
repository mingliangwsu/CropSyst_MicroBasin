#include "soilprofileclass2.h"
//______________________________________________________________________________
#ifdef MSVB_CASCADE_INFILTRATION_HOUR
//140429 RLN this should eventually be replaced by Roger's code

void SoilProfileClass::assignApparentKsat()
{
    //(kg*s/m3) Determine apparent hydraulic conductivity that matches field capacity characteristics
    double WC_sat_layer;

    double FC_layer;
    double PWP_layer;

    double water_pot_at_FC_layer;
    double b_value_layer;
    double m_layer;
    double one_minus_m_layer;
    double m_minus_one_layer;
    double thickness_layer;
    double hours_to_field_capacity_layer;
    //standard_gravity


    for (int layer=1; layer <= /*LML 14/05/07 Number_Of_Total_Nodes*/ NuL + 3; layer++) {
        water_pot_at_FC_layer = FC_WPot[layer]; //soil.properties.hydraulics.get_water_pot_at_FC(layer);
        PWP_layer = Permanent_Wilting_Point[layer];// soil.properties.hydraulics.get_permanent_wilt_point_volumetric(layer);
        thickness_layer = Layer_Thickness_m[layer];//soil.properties.layers.get_thickness_m(layer);
        WC_sat_layer = Saturation_Water_Content[layer];//soil.properties.hydraulics.get_saturation_water_content_volumetric(layer);
        FC_layer = Field_Capacity[layer];//soil.properties.hydraulics.get_field_capacity_volumetric(layer);
        //double b_value_layer_1 = (CORN_ln(1500.0) - CORN_ln(-water_pot_at_FC_layer) )/ (CORN_ln(FC_layer / WC_sat_layer) - CORN_ln(PWP_layer / WC_sat_layer));
        double b_value_layer = b_Value[layer];//soil.properties.hydraulics.get_Campbell_b(layer,false);
        //double b_value_layer_3 = soil.properties.hydraulics.get_Campbell_b(layer,1);

        m_layer = 2.0 * b_value_layer + 3.0;
        one_minus_m_layer = 1.0 - m_layer;
        m_minus_one_layer = m_layer - 1.0;

        hours_to_field_capacity_layer = Hours_To_Field_Capacity[layer];      //hours_to_field_capacity[L];

        /*Apparent_K_Sat[layer] = thickness_layer * WaterDensity_kg_m3   //    Apparent_K_Sat(Layer) = Layer_Thickness(Layer) * Water_Density
                * pow(WC_sat_layer , m_layer)
                * (pow(FC_layer , one_minus_m_layer)                                 //         * WC_Sat(Layer) ^ (m(Layer)) * (FC(Layer) ^ (1 - m(Layer))
                   - pow(WC_sat_layer , one_minus_m_layer))                          //        - WC_Sat(Layer) ^ (1 - m(Layer)))
                / (standard_gravity * hours_to_field_capacity_layer
                   * 3600.0 * m_minus_one_layer);                                    //        / (Gr * Hours_To_Field_Capacity(Layer) * 3600 * (m(Layer) - 1))
        Apparent_K_Sat[layer] = std::max<double>(Apparent_K_Sat[layer],1.0e-9); // If Apparent_K_Sat(Layer) < 0 Then Apparent_K_Sat(Layer) = 0.0000000001*/

        Apparent_K_Sat[layer] = calcApparentKSat(thickness_layer,WC_sat_layer,m_layer,FC_layer,hours_to_field_capacity_layer);
    }
};
//______________________________________________________________________________
double SoilProfileClass::calcApparentKSat(double thickness,double WC_sat,double m,double FC, double hours_to_field_capacity)
{
    double out;
    out = thickness * WaterDensity_kg_m3                            //    Apparent_K_Sat(Layer) = Layer_Thickness(Layer) * Water_Density
            * pow(WC_sat, m)
            * (pow(FC, 1.0-m)                                       //         * WC_Sat(Layer) ^ (m(Layer)) * (FC(Layer) ^ (1 - m(Layer))
               - pow(WC_sat, 1.0-m))                                //        - WC_Sat(Layer) ^ (1 - m(Layer)))
            / (standard_gravity * hours_to_field_capacity
               * 3600.0 * (m-1.0));                                 //LML 14/04/28 fixed an error

    out = std::max<double>(out,1.0e-9);
    return out;
}
#endif
//______________________________________________________________________________
#ifdef MSVB_CASCADE_INFILTRATION_HOUR
//140429 RLN this should eventually be replaced by Roger's code
void SoilProfileClass::assignHoursToFieldCapacity()
{
    double clay_percentage;
    for (int i = 1; i <= NumberOfLayers(); i++) {
        clay_percentage = Clay_Percentage[i];
        Hours_To_Field_Capacity[i] = calHoursToFieldCapacity(clay_percentage);      //properties.layers.parameters.horizon_clay);
    }
}
#endif
//______________________________________________________________________________
#ifdef MSVB_CASCADE_INFILTRATION_HOUR

double SoilProfileClass::calcK_satForHr2FC(int layer)
{
    //RS: this function calculates the Ks required to meet the hours to field capacity premisses

    const double Water_Density = 1000.0;  //(kg/m3)
//140506    const double Gr = 9.8;  //Gravitational constant in m/s2

    double K_satForHr2FC = Layer_Thickness_m[layer] * Water_Density
            * pow(Saturation_Water_Content[layer], (m_Value[layer]))
            * (pow(Field_Capacity[layer],(1.0 - m_Value[layer]))
                   - pow(Saturation_Water_Content[layer],(1.0 - m_Value[layer])))
                   / (standard_gravity * Hours_To_Field_Capacity[layer] * 3600.0 * (m_Value[layer] - 1.0)); //140506RLN
    return K_satForHr2FC;
}
#endif

