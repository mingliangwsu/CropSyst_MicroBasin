#ifndef CropSyst_LCA_carbon_footprint_receiverH
#define CropSyst_LCA_carbon_footprint_receiverH
namespace CropSyst
{
namespace LCA_Carbon_footprint
{

//______________________________________________________________________________
public interface class IReceiver
{
 public:
   bool know_SOM_initial_final_CO2_Mg_ha
      (int initial_year, float SOM_CO2_initial_Mg_ha
      ,int final_year, float SOM_CO2_final_Mg_ha);
   bool know_N2O_CO2e_Mg_ha       (int year, float N2O_emission_CO2e_Mg_ha);
   int know_event
      (int     date
      ,System::String ^ID
      ,System::String ^type
      ,System::String ^NRCS_field_op
      ,System::String ^operation_filename
      ,float   amount
      ,System::String ^amount_units
      )  ;
      /**
         Derived classes must override this methods for tallying
         the carbon footprint of operations.


       Returns the status of the performed event.
         For management operations, the return value will usually be ES_COMPLETE
         inicating the event was actually performed.

         Date of the scheduled event
            Derived classes can expect this method to be called in
            chronological order.

         ID
            The identifier of the management operation as specified in the
            defining scenario, management, operation, or rotation file.
            Note that
            Some operations/events are generated by the simulation,
            these will not have the operation filename (blank).
            The OFoot scenario editor may automatically generate ID's.
            OFoot LCA analysis should used the ID to lookup
            operational parameters in the OFoot scenario file as needed.

         type
            The type of event this will be included for all events.
            The value string is case sensitive.

               Crop events:
                  Active growth
                  Begin flowering
                  Grain filling
                  Maturity
                  biomass_fate
                     (Crop biomass distribution occuring with
                     harvest, tillage, residue plant death.
                      This can be ignored for OFoot)

               Management operations:
                  Harvest
                  Tillage
                  Irrigation
                  Inorganic nitrogen
                  type=Sowing

               Other (simulation control):
                  Start
                  Stop

               There may also start and stop of automatic management periods.
               The analyze_operation_event method might not be invoked
               for these events.

            Note that management files specify operation_type
            of management operations (with values written in upper case).
            The operation_type value is NOT reported here.


         NRCS_field_op
            NRCS (from RUSLE2) database table  of operation/implements.
            This will match the NRCS_field_op on the parameter file.
            (Note that there could be operations generated by the
            simulation run in addition to scheduled management operations
            such as crop termination or other automatic operations
            but these will typically not involve equipment/implements
            and will not have carbon foot print).

         amount
            This is the amount of product/commodity applied.
            For irrigation this is the depth of water applied.
            Currently OFoot needs only irrigation depths.

         amount_units
            The units of the applied amount.
            These will typically be   mm or m  (for water depth)
            kg/m� (chemical concentration)
            kg/ha  (mass, or mass of nitrogen or mass of carbon)
               Usually mass reported here is kg/ha but
               there could be kg/m� or kg/m2 it may be necessary
               to check the units code for some operations.

            irrigation will be reported in mm.

         operation_filename
            The operation_filename parameter identifies
            the file where the user specified operation/event is defined.
            CropSyst/CANMS/CAFE Dairy could have multiple sources of
            defined operations.  In the case of OFoot there will probably
            only be one scenario parameter file.
            This field will be blank for generated events

         operation_type
            The value string is case sensitive.
            Value will be one of the following:
            INORGANIC_NITROGEN
            HARVEST

      **/
};
//______________________________________________________________________________
}; // namespace LCA_Carbon_footprint
}; // namespace CropSyst



#endif