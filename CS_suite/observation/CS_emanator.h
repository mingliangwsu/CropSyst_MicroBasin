#ifndef CS_emanatorH
#define CS_emanatorH
#include "corn/container/enumlist.h"
#include "corn/container/text_list.h"
#include "corn/chronometry/temporal.h"
namespace CS {
//______________________________________________________________________________
class Emanator
: public extends_ CORN::Enumeration
{public:
   enum Status
      { unknown_status
      , normal_status
      , stopped_status                                                           //170521
      , deleted_status};
 public:
      // We dont reference this Meta information in the emanating object
      // because it may be deleted at any time.
   std::string                instance_name;
      // Partial path used to compose instance qualification.
      // Typically this will the ID/key used to uniquely identify
      // the instanciated objected.
      // This is usually provided by the user.
      // Recoder will use this to compose directory
   std::string                ontology_domain; // of the property of the object's class
      // Partial path used to compose property ontology
      // Typically this will be a single word representing.
      // It is analygous to the ontology specified for inspectors.
      // It will be included in the composition of qualified ontolgy

   /* NYN
   std::string                URL;
      // The unqualified URL name may be used to specify the target of inspection outputs.
      // By default URL is the same as the instance label
      // However it may be set specifically.
      // For example, in CropSyst the URL will match the crop parameter file name
      // (so the outputs for the same time of crop go in the same
      //  target directory UED file(s)).
   */
      bool ephemeral;
 protected:
   nat32                      ID;
   const Emanator         *context;
      // Parent container.
      // Will be 0 when root.
 protected:
   Status      status;
 public:
   Emanator
      (nat32                ID
      ,const std::string   &instance_name
      ,const std::string   &ontology
      ,bool                 ephemeral
      ,const Emanator      *context);
   virtual ~Emanator();
 public: // enumeration implementation
   inline virtual bool is_key_nat32(nat32 key) affirmation_ { return ID == key;} //180820
   inline virtual nat32 get_key_nat32()                     const { return ID; }
 public:
   inline bool   is_ephemeral()              affirmation_ { return  ephemeral; }
   inline bool   is_relevant_annually()      affirmation_ { return !ephemeral; } //170319

      // Currently ephemeral objects are not tallied annually
   inline Status get_status()                           const { return status; }
   inline Status set_status(Status new_status)                     assignation_
      { status = new_status; return status; }
   const char *append_ontology_domain_name_to
      (std::string &append_to,char delimiter=0)                           const; //170322
   nat16 list_instance_path   (CORN::Text_list &qualified_instance)       const;
      // Recursively lists the elements of the instance path
      // The instance path would typically represent the
      // structural composition of object instances.
      // In CropSyst this is used to compose output directory/filenames.
};
//_2015-08-18___________________________________________________class Emanator_/
class Emanators
: public extends_ CORN::Enumeration_list // list of Emanators
{
   const CORN::Temporal &temporality_curr;
      // reference to the driving date datetime or time
 public:
   Emanators
      (const CORN::Temporal &temporality_curr);                                  //171115
   Emanator &know
      (nat32                emanator_ID
      ,const std::string   &instance_name
      ,const std::string   &ontology
      ,bool                 ephemeral                                            //160616
      ,const Emanator      *context
      ,const CORN::Temporal &temporality);                                       //171115
      // A recording object will register itself with
      // with the global variable recorders list.
      // It can either do this in its constructor (or initializer)
      // or whenever it starts adding listeners.
      // (this can be called multiple times, but only
      //  one Variable recorder is uniquely added to the list).
      // \returns the identified Emanator
   bool forget(nat32 emanator_ID)                                   ; //cognition_;
      // A emanator object destructor should deregister
      // itself with the global emanators.
      // \return true if (emanator found), false is not an error.
   Emanator::Status get_status_of(nat32 emanator_ID)                      const;
   bool start_year()                                              modification_;
   bool end_year()                                                modification_;
   bool start(CORN::datetime64 inception_date)                    modification_; //170413
   bool stop()                                                    modification_;
};
//_2015-08-18_________________________________________________class Emanators__/
extern Emanators &instantiate_emanators(const CORN::Temporal &temporality_curr); //171115
extern Emanators &get_emanators();                                               //171115
extern Emanators *emanators_global;                                              //180115LML
} // namespace CS
#endif

