#ifndef LADSS_datasrcH
#define LADSS_datasrcH

#ifdef LADSS_ORACLE
#  include "corn/data_source/oracle_datasrc.h"
CORN::Oracle_server_session *oracle_session;
#  define LADSS_database_schema        "LADSS",
// Note June 13, Kevin decided to have both input and output
// in the LADSS schema (before output was in CROPSYST schema.
#  define database_session       ,*oracle_session
#  define Database_data_source   Oracle_SQL_data_source
// Oracle DS currently always presumes the table already exists
// (We don't have facilities to create Oracle tables)
// So flags for creating tables are not specified.
#  define table(table_name)  table_name
#  define AUTOMATICALLY_SEQUENCE_PRIMARY_KEY(table)  table->automatically_sequence_primary_key()
#else
#  define LADSS_database_schema
#  define database_session
#ifdef unix
//061117 Currently I have this disabled for UNIX because
// the Dynamic_int32_indexed_dBase_data_source is not compiling under SunStudio
// I currently don't need to test the database emulation under UNIX
#  include "corn/data_source/vv_file.h"
#  define Database_data_source VV_file
#else

// This dbase include is to allow Roger to
// Compile LADSS mode on his PC without needing Oracle
// The dbase_datasrc is a close surragate for the oracle datasrc
// dbase_datasrc does not require a session thus we use database_session macro to exclude this parameter
//060601 check needed #  include <corn/format/dbase_datasrc.h>
// Database session and schema do not apply to dBase
#  define Database_data_source   Dynamic_int32_indexed_dBase_data_source
// The dbase data source requires a flag indicating if the
// table is to be created or already exists.
//021206 appears to be obolsete #  define DB_CREATE  ,true
//021206 appears to be obolsete #  define DB_EXISTS  ,false
#endif

#  define table(table_name)  (CORN::OS::File_name_concrete(0,table_name,"dbf").c_str())

// Data_source_dBase doesn't have automatically_sequence_primary_key
#define AUTOMATICALLY_SEQUENCE_PRIMARY_KEY(table)
#endif

#define LABEL_database           "database"
#define LABEL_user_ID            "user_ID"
#define LABEL_password           "password"

#endif
// LADSS_datasrc.h

