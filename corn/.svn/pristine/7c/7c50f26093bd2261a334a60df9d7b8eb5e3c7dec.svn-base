#ifndef ORACLE_DATASRCH
#define ORACLE_DATASRCH

#include "corn/format/datasrc.h"
#include "corn/container/association.h"
#include "corn/string/cstrngem.h"

#include <oci.h>
namespace CORN {

class Oracle_SQL_data_source; // forward declaration
//______________________________________________________________________________
class Oracle_server_session
{  friend class Oracle_SQL_data_source;
private:
   CORN_string user_name;
   CORN_string password;
public: // Oracle control structures and pointers
    OCIEnv     *envhp;  /* the environment handle     */
    OCIError   *errhp;  /* the error handle           */
    OCIServer  *srvhp;  /* the server handle          */
    OCISvcCtx  *svchp;  /* the service context handle */
    OCISession *usrhp;  /* the user session handle    */
public:
   Oracle_server_session(const char *user_name,const char *password);
   ~Oracle_server_session();
   bool check_errors(sword status);
   // returns true if successful
};
//______________________________________________________________________________
class Oracle_SQL_data_source
: public Data_source
{
private:
   CORN_string             database_name;
   CORN_string             table_name;
   CORN_string             primary_key;
   bool                    auto_sequence_primary_key;
   // If true, the primary key field is automatically sequenced
   // using the SQL NEXTVAL keyword instead of binding to the respective field
   // This is used for output only.
   CORN_string             order_by_attribute;
   // If specified the order by clause will be appended to the SELECT statement
   Association_list        field_conversion_buffers;
   Association_list        existing_table_attributes;
private:
   Oracle_server_session  &server_session;
   OCIStmt                *statement_handle_pointer;
   bool                    created;
   bool always_setup_INSERT_and_SELECT_for_each_record;
private: // Optimization variables
   CORN_string INSERT_INTO_columns_VALUES;
   CORN_string SELECT_columns_FROM_table;
   CORN_string get_where_clause;
   CORN_string select_from_table_statement;
private: // Methods specific to Oracle data source
   bool insert(Data_record &data_rec);
   // Actually this appends a record (I am using SQL nomenclature here)
   bool update(Data_record &data_rec);
   bool load_attributes();
   bool free_statement_handle_pointer();
   bool bind_fields(Data_record &data_rec);
   // binds the fields to the data record.
   inline CORN_string get_INSERT_INTO_columns_VALUES();
   inline CORN_string get_SELECT_columns_FROM_table();
//public:
   void setup_INSERT_and_SELECT_statements(Data_record &from_record);
public:
   Oracle_SQL_data_source
      (const char *i_database_name  // Also known as schema
      ,const char *i_table_name
      ,const char *i_primary_key
      , Oracle_server_session &i_server_session);
   ~Oracle_SQL_data_source();
   virtual void automatically_sequence_primary_key();
   virtual void order_by(const char *attribute);
      // This sorts the data by the specified attribute
      // in 'get' methods, this should be called before get().
   virtual bool create(Data_record &from_record);
      // Currently the create does not create the table in the database
      // we currently presume the table is already created in the database.
      // But we do setup buffer and SQL strings.
   virtual bool get(Data_record &data_rec);
   virtual bool get_next(Data_record &data_rec);
      // In SQL the where clause may return more than one record.
      // In this case, use get() to fetch the first record
      // and repeat calling get_next to fetch remaining records.
      // get_next will return false if there were no
      // additional records returned by the SELECT WHERE statement to fetch.
   // //170424 replaced with label_wstring virtual const char *label_cstr_deprecated(char *buffer)                const;
   virtual const char *label_string(std::string &buffer)                  const;
   virtual void where_long(const char *attribute, const long value);
   virtual void where_cstr(const char *attribute, const char *value);
      // This sets up a where clause to index a field.
      // The attribute column should have unique values.
   virtual void where2_long
        (const char *attribute1, const long value1
        ,const char *attribute2, const long value2);
      // This is a where clause with two key attribute
   virtual bool delete_records();
      // To select the records to be delete, set up a where clause with
      // one of the where_xxxx() functions;
   inline void setup_INSERT_and_SELECT_for_each_record()
      { always_setup_INSERT_and_SELECT_for_each_record = true;}
protected:
   virtual bool set_data(Data_record &data_rec,bool append);                     //150503
private:
   inline bool check_errors(sword status)
      { return server_session.check_errors(status); }
};
//______________________________________________________________________________
}; // namespace CORN

#endif

