
Attribute VB_name = "Texture_hydraulics"
' Module name

' This Visual Basic module requires the dll file texture_hydraulics.dll.
' Put the texture_hydraulics.dll in a place accessable to the MicroSoft compiler
' or Microsoft product (Excel) that will use this module dll.
' (I.e. in \Windows\system32 directory).

' To use this dll in Excel:
' - Click Alt-F11 to start the Visual Basic for applications IDE.
' - Select the menu "File/Import file"
' - In the "Import file" requestor, select the .BAS program that matches the DLL.
'    This will add a module to your project's "Modules" list.
'    Note that the module name matches the VB_name attribute specified in the .BAS file.

Option Explicit

Declare Function set_soil_texture Lib "Texture_hydraulics.dll" (ByVal sand as Single,ByVal clay as Single,ByVal silt as Single) as Integer
' This function resets all calculations for the specified texture.
' It should be called to calculate the properties for each texture.
' All fixed properties are cleared and estimated values are calculated.
' Texture values are in percent  0 to 100.

' The following functions are optional to set known fixed values for the soil.
' If fixed values are not set they will be estimated from texture
' and/or other fixed values.
' (The functions return the value that was set).

' Only call these functions after calling setup_soil_texture_hydraulics()
' because setup_soil_texture_hydraulics recalculates all properties replacing any fixed values.
' Calling any one of these functions recomputes all properties
' that have not been fixed.

Declare Function fix_vol_WC_at_1500 Lib "Texture_hydraulics.dll" (ByVal fixed_vol_WC_at_1500 as Single) as Single
' m3/m3   water content at permanent wilt point (matric potential -1500 kPa)

Declare Function fix_vol_WC_at_33 Lib "Texture_hydraulics.dll" (ByVal fixed_vol_WC_at_33 as Single) as Single
' m3/m3   water content at field capacity  (matric potential -33 kPa)

Declare Function fix_bulk_density Lib "Texture_hydraulics.dll" (ByVal fixed_bulk_density as Single) as Single
' grams/cm3  bulk density

Declare Function fix_sat_hydraulic_cond_m_d Lib "Texture_hydraulics.dll" (ByVal fixed_sat_hydraulic_cond as Single) as Single
' m/day  saturated hydraulic conductivity

Declare Function fix_air_entry_pot Lib "Texture_hydraulics.dll" (ByVal fixed_air_entry_pot as Single) as Single
' J/kg  air entry potential

' The following functions return the current estimated, calculated or fixed values.

Declare Function get_saturation Lib "Texture_hydraulics.dll" () as Single
' m3/m3

Declare Function get_vol_WC_at_1500 Lib "Texture_hydraulics.dll" () as Single
' m3/m3  water content at permanent wilt point (matric potential -1500 kPa)

Declare Function get_WC_at_33 Lib "Texture_hydraulics.dll" () as Single
' m3/m3  water content at field capacity  (matric potential -33 kPa)

Declare Function get_bulk_density Lib "Texture_hydraulics.dll" () as Single
' grams/cm3  bulk density

Declare Function get_sat_hydraulic_cond_m_d Lib "Texture_hydraulics.dll" () as Single
' m/day  saturated hydraulic conductivity

Declare Function get_sat_hydraul_cond_cm_hr Lib "Texture_hydraulics.dll" () as Single
' cm/hr   same as get_sat_hydraulic_cond_m_d but converted to cm/hr

Declare Function get_air_entry_pot Lib "Texture_hydraulics.dll" () as Single
' J/kg   air entry potential

Declare Function get_b Lib "Texture_hydraulics.dll" () as Single
' unitless  Campbell b coefficient

Declare Function get_geometric_mean_particle_size Lib "Texture_hydraulics.dll" () as Single
' micrometers ?
