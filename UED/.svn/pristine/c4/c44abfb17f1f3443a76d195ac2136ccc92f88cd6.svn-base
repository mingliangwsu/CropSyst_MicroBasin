object tabular_format_editor_form: Ttabular_format_editor_form
  Left = 233
  Top = 179
  Width = 729
  Height = 678
  Caption = 'Tabular format editor'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl_TDF_editor: TPageControl
    Left = 0
    Top = 0
    Width = 721
    Height = 644
    ActivePage = tabsheet_information
    Align = alClient
    TabOrder = 0
    object tabsheet_information: TTabSheet
      Caption = 'Information'
      object Label1: TLabel
        Left = 16
        Top = 24
        Width = 51
        Height = 13
        Caption = 'Defined by'
      end
      object Label19: TLabel
        Left = 80
        Top = 48
        Width = 357
        Height = 13
        Caption = 
          'Enter here the contact info for the person describing this forma' +
          't (your name).'
      end
      object Label20: TLabel
        Left = 32
        Top = 80
        Width = 64
        Height = 13
        Caption = 'Defined date '
      end
      object Label21: TLabel
        Left = 24
        Top = 594
        Width = 62
        Height = 13
        Anchors = [akLeft, akBottom]
        Caption = 'Version 0.0.1'
      end
      object defined_by_edit: TAutoStringEdit
        Left = 80
        Top = 24
        Width = 626
        Height = 21
        Anchors = [akLeft, akTop, akRight]
        TabOrder = 0
      end
      object defined_date_button: TAutoDateButton
        Left = 112
        Top = 80
        Width = 281
        Height = 25
        Caption = 'Defined date'
        TabOrder = 1
      end
      object RadioGroup1: TRadioGroup
        Left = 24
        Top = 120
        Width = 674
        Height = 105
        Anchors = [akLeft, akTop, akRight]
        Caption = 'NYI Applicability'
        Items.Strings = (
          'Not usable (I.e. incomplete or preliminary)'
          
            'Import (I.e. if only relevent fields to be read have been define' +
            'd)'
          'Export (I.e. not all possible outputs have been defined)'
          'Import and Export (complete)')
        TabOrder = 2
        Visible = False
      end
    end
    object tabsheet_file_type: TTabSheet
      Caption = 'File type'
      ImageIndex = 1
      object format_file_type_label: TLabel
        Left = 8
        Top = 48
        Width = 71
        Height = 13
        Caption = 'Format file type'
      end
      object Label22: TLabel
        Left = 24
        Top = 184
        Width = 666
        Height = 49
        Anchors = [akLeft, akTop, akRight]
        AutoSize = False
        Caption = 
          'NYI If you have an existing UED database and or an existing file' +
          ' of the specified format file type, use "Example file layout" to' +
          ' help check the format definition.'
        Visible = False
        WordWrap = True
      end
      object format_file_type_combo: TAutoLabeledEnumComboBox
        Left = 120
        Top = 48
        Width = 586
        Height = 21
        Style = csDropDownList
        Anchors = [akLeft, akTop, akRight]
        ItemHeight = 13
        TabOrder = 0
        OnChange = format_file_type_combo_onchange
      end
      object big_endian_checkbox: TAutoCheckBox
        Left = 120
        Top = 72
        Width = 337
        Height = 17
        Hint = 'Binary datum byte order'
        Caption = 'Big endian (binary)'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
      end
      object text_file_type_groupbox: TGroupBox
        Left = 8
        Top = 88
        Width = 698
        Height = 89
        Anchors = [akLeft, akTop, akRight]
        Caption = 'Text file type options'
        TabOrder = 2
        object carriage_return_line_feed_checkbox: TAutoCheckBox
          Left = 24
          Top = 24
          Width = 666
          Height = 17
          Anchors = [akLeft, akTop, akRight]
          Caption = 
            'New lines include carriage return and line feed (check for DOS/W' +
            'indows text files, uncheck for UNIX)'
          TabOrder = 0
        end
        object fortran_carriage_control_checkbox: TAutoCheckBox
          Left = 24
          Top = 56
          Width = 666
          Height = 17
          Hint = 
            'Reserve the first character in the line for FORTRAN style carria' +
            'ge control'
          Anchors = [akLeft, akTop, akRight]
          Caption = 'FORTRAN carriage control'
          ParentShowHint = False
          ShowHint = True
          TabOrder = 1
          OnClick = fortran_carriage_control_checkboxClick
        end
      end
      object sample_file_button: TButton
        Left = 8
        Top = 8
        Width = 698
        Height = 25
        Anchors = [akLeft, akTop, akRight]
        Caption = 
          'Automatically detect file type and some basic information from a' +
          ' sample file with the format being defined.'
        TabOrder = 3
        OnClick = sample_file_button_onclick
      end
    end
    object tabsheet_parsing: TTabSheet
      Caption = 'Parsing'
      ImageIndex = 6
      object AutoRadioGroup1: TAutoRadioGroup
        Left = 8
        Top = 0
        Width = 217
        Height = 57
        Caption = 'Data to be parsed begins relative to '
        Items.Strings = (
          'Beginning of file'
          'Begin data marker')
        TabOrder = 0
      end
      object markers_panel: TPanel
        Left = 8
        Top = 64
        Width = 617
        Height = 297
        TabOrder = 1
        object label_begin_marker: TLabel
          Left = 8
          Top = 8
          Width = 62
          Height = 13
          Caption = 'Begin marker'
        end
        object label_end_marker: TLabel
          Left = 8
          Top = 32
          Width = 54
          Height = 13
          Caption = 'End marker'
        end
        object Label14: TLabel
          Left = 8
          Top = 56
          Width = 601
          Height = 41
          Anchors = [akLeft, akTop, akRight]
          AutoSize = False
          Caption = 
            'Text file and spreadsheets might have extraneous text not relate' +
            'd to the data to be imported/exported which is delimited by begi' +
            'n/end markers.  '
          Color = clInfoBk
          ParentColor = False
          WordWrap = True
        end
        object Label30: TLabel
          Left = 7
          Top = 104
          Width = 601
          Height = 41
          Anchors = [akLeft, akTop, akRight]
          AutoSize = False
          Caption = 
            'Data markers are optional, if not specified, the data is assumed' +
            ' to start at the beginning of the file (Or the upper left spread' +
            'sheet cell).'
          Color = clInfoBk
          ParentColor = False
          WordWrap = True
        end
        object Label28: TLabel
          Left = 7
          Top = 152
          Width = 601
          Height = 41
          Anchors = [akLeft, akTop, akRight]
          AutoSize = False
          Caption = 
            'When importing,  any text/cells before the begin marker (if spec' +
            'ified) and after the end marker (if specified)  is ignored. For ' +
            'example data that has been sent  in an email message might have ' +
            'some code indicating the start of data to exclude email headers'
          Color = clInfoBk
          ParentColor = False
          WordWrap = True
        end
        object Label29: TLabel
          Left = 7
          Top = 200
          Width = 601
          Height = 41
          Anchors = [akLeft, akTop, akRight]
          AutoSize = False
          Caption = 
            'The begin and and markers can be the same text. For example one ' +
            'could bound the data block with  five dashes -----. In this case' +
            ', the first occurance indicates the start of the data, and the s' +
            'econd, the end of the data.'
          Color = clInfoBk
          ParentColor = False
          WordWrap = True
        end
        object Label31: TLabel
          Left = 7
          Top = 248
          Width = 601
          Height = 41
          Anchors = [akLeft, akTop, akRight]
          AutoSize = False
          Caption = 
            'If the  begin marker is at the end of the line,  data starts wit' +
            'h the next line in the file, otherwise data is assumed to begin ' +
            'immediately following the begin marker string (on the same line)' +
            '.  '
          Color = clInfoBk
          ParentColor = False
          WordWrap = True
        end
        object edit_begin_marker: TAutoStringEdit
          Left = 80
          Top = 8
          Width = 529
          Height = 21
          Anchors = [akLeft, akTop, akRight]
          TabOrder = 0
        end
        object edit_end_marker: TAutoStringEdit
          Left = 80
          Top = 32
          Width = 529
          Height = 21
          TabOrder = 1
        end
      end
      object checkbox_paginated: TAutoCheckBox
        Left = 240
        Top = 16
        Width = 458
        Height = 17
        Anchors = [akLeft, akTop, akRight]
        Caption = 'Paginated with FormFeed (ASCII code 12)'
        TabOrder = 2
      end
    end
    object tabsheet_detail_lines: TTabSheet
      Caption = 'Detail lines'
      ImageIndex = 5
      object PageControl3: TPageControl
        Left = 0
        Top = 0
        Width = 713
        Height = 616
        ActivePage = tabsheet_text_and_spreadsheet_format
        Align = alClient
        TabOrder = 0
        object tabsheet_text_and_spreadsheet_format: TTabSheet
          Caption = 'Text and spreadsheet formats'
          object Label12: TLabel
            Left = 8
            Top = 16
            Width = 42
            Height = 13
            Caption = 'Start row'
          end
          object Label15: TLabel
            Left = 8
            Top = 136
            Width = 97
            Height = 25
            AutoSize = False
            Caption = 'File detail lines per UED record'
            WordWrap = True
          end
          object Label16: TLabel
            Left = 104
            Top = 168
            Width = 594
            Height = 41
            Anchors = [akLeft, akTop, akRight]
            AutoSize = False
            Caption = 
              'The number of data record lines in the data file to be used to c' +
              'reate a UED record.    When 0 (not specified), the record count ' +
              'of the file will be used. (used for importing). For daily data t' +
              'his will normally be 366 (days per record).'
            Color = clInfoBk
            ParentColor = False
            WordWrap = True
          end
          object Label17: TLabel
            Left = 8
            Top = 72
            Width = 80
            Height = 13
            Caption = 'Record time step'
          end
          object Label18: TLabel
            Left = 104
            Top = 104
            Width = 594
            Height = 25
            Anchors = [akLeft, akTop, akRight]
            AutoSize = False
            Caption = 
              'The time step represented by each row of data. It is not necessa' +
              'ry to specify the time step if there is one (or more) columns) w' +
              'hich have the record date and/or time.'
            Color = clInfoBk
            ParentColor = False
            WordWrap = True
          end
          object data_start_row_edit: TAutoInt16Edit
            Left = 72
            Top = 16
            Width = 70
            Height = 24
            Hint = 
              'Enter 0 if not applicable, that is the detail lines start at the' +
              ' beginning of the file.'
            Alignment = taRightJustify
            Lines.Strings = (
              '0')
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
          end
          object records_per_UED_record_edit: TAutoInt16Edit
            Left = 104
            Top = 136
            Width = 70
            Height = 24
            Alignment = taRightJustify
            Lines.Strings = (
              '0')
            TabOrder = 1
          end
          object time_step_edit: TAutoInt16Edit
            Left = 104
            Top = 72
            Width = 70
            Height = 24
            Alignment = taRightJustify
            Lines.Strings = (
              '0')
            TabOrder = 2
          end
          object record_type_step_units_button: TAutoUnitsButton
            Left = 184
            Top = 72
            Width = 257
            Height = 25
            Caption = 'Time step units'
            TabOrder = 3
          end
          object data_start_row_relative_radiogroup: TAutoRadioGroup
            Left = 152
            Top = 0
            Width = 313
            Height = 65
            Caption = 'Relative to (1 based)'
            Columns = 2
            Items.Strings = (
              'Beginning of file'
              'Beginning of data (marker)'
              'Line on page/Row on sheet'
              'Last column header row')
            TabOrder = 4
          end
        end
        object detail_lines_delineation_tabsheet: TTabSheet
          Caption = 'Delineation'
          ImageIndex = 1
        end
      end
    end
    object TabSheet4: TTabSheet
      Caption = 'Column headers'
      ImageIndex = 3
      object PageControl2: TPageControl
        Left = 0
        Top = 0
        Width = 713
        Height = 329
        ActivePage = tabsheet_column_headers
        Align = alTop
        TabOrder = 0
        object tabsheet_column_headers: TTabSheet
          Caption = 'Text and spreadsheet formats'
          object Label33: TLabel
            Left = 48
            Top = 248
            Width = 3
            Height = 13
          end
          object groupbox_col_headers_text: TGroupBox
            Left = 0
            Top = 217
            Width = 705
            Height = 80
            Align = alTop
            Caption = 'Overriding column header text'
            TabOrder = 0
            object Label2: TLabel
              Left = 2
              Top = 40
              Width = 701
              Height = 38
              Align = alBottom
              AutoSize = False
              Caption = 
                'Usually column header captions are generated  from /Columns\ cap' +
                'tion text). In some formats fixed column width captions don'#39't al' +
                'ign with detail line data values. This input allows for fixed co' +
                'lumn header text to be used instead of generated captions.'
              Color = clInfoBk
              ParentColor = False
              WordWrap = True
            end
            object edit_col_headers_text: TAutoStringEdit
              Left = 8
              Top = 16
              Width = 690
              Height = 21
              Anchors = [akLeft, akTop, akRight]
              TabOrder = 0
            end
          end
          object groupbox_col_headers_start_row: TGroupBox
            Left = 0
            Top = 0
            Width = 705
            Height = 57
            Align = alTop
            Caption = 'Start row'
            TabOrder = 1
            object Label4: TLabel
              Left = 136
              Top = 24
              Width = 238
              Height = 13
              Anchors = [akLeft, akTop, akRight]
              Caption = '1 based (0=no column headers)'
            end
            object column_header_start_row_relative_radiogroup: TAutoRadioGroup
              Left = 382
              Top = 15
              Width = 321
              Height = 40
              Align = alRight
              Caption = 'Relative to'
              Columns = 2
              Items.Strings = (
                'Beginning of file'
                'Beginning of data (marker)'
                'Line on page/Row on sheet')
              TabOrder = 0
            end
            object column_header_start_row_edit: TAutoInt16Edit
              Left = 64
              Top = 16
              Width = 70
              Height = 24
              Alignment = taRightJustify
              Lines.Strings = (
                '0')
              TabOrder = 1
            end
            object checkbox_column_headers_every_page: TAutoCheckBox
              Left = 16
              Top = 40
              Width = 682
              Height = 17
              Anchors = [akLeft, akTop, akRight]
              Caption = 'Column headers appear on every page (if paginated)'
              TabOrder = 2
            end
          end
          object groupbox_col_headers_rows: TGroupBox
            Left = 0
            Top = 57
            Width = 705
            Height = 64
            Align = alTop
            Caption = 'Rows'
            TabOrder = 2
            object Label6: TLabel
              Left = 144
              Top = 16
              Width = 357
              Height = 13
              Anchors = [akLeft, akTop, akRight]
              Caption = 'Enter the number of rows devoted to column header info.'
            end
            object Label7: TLabel
              Left = 144
              Top = 32
              Width = 553
              Height = 25
              Anchors = [akLeft, akTop, akRight]
              AutoSize = False
              Caption = 
                'Enter 0 if no column headers. (If this is a format to export (cr' +
                'eating) to Excel, you can enter 1 for multiline cells)'
              WordWrap = True
            end
            object column_header_rows_edit: TAutoInt16Edit
              Left = 64
              Top = 16
              Width = 70
              Height = 24
              Alignment = taRightJustify
              Lines.Strings = (
                '0')
              TabOrder = 0
            end
          end
          object groupbox_col_headers_units: TGroupBox
            Left = 0
            Top = 121
            Width = 705
            Height = 96
            Align = alTop
            Caption = 'Units'
            TabOrder = 3
            object Label8: TLabel
              Left = 8
              Top = 16
              Width = 48
              Height = 13
              Caption = 'Offset row'
            end
            object Label9: TLabel
              Left = 152
              Top = 16
              Width = 449
              Height = 33
              AutoSize = False
              Caption = 
                'One of the column header rows may be used to specify the units. ' +
                'Enter the offset from the start of the column row (I.e. 0 if the' +
                ' first row of the column header is the units.)'
              WordWrap = True
            end
            object Label32: TLabel
              Left = 24
              Top = 32
              Width = 127
              Height = 13
              Anchors = [akLeft, akTop, akRight]
              Caption = '0 based'
            end
            object Label10: TLabel
              Left = 8
              Top = 48
              Width = 27
              Height = 13
              Caption = 'Rows'
            end
            object Label11: TLabel
              Left = 152
              Top = 48
              Width = 441
              Height = 33
              AutoSize = False
              Caption = 
                'Enter the number of rows used to print the units (usually 1). En' +
                'ter 0 if no units row.'
              WordWrap = True
            end
            object column_header_units_row_edit: TAutoInt16Edit
              Left = 80
              Top = 16
              Width = 57
              Height = 24
              Alignment = taRightJustify
              Lines.Strings = (
                '0')
              TabOrder = 0
            end
            object column_header_units_rows_edit: TAutoInt16Edit
              Left = 80
              Top = 48
              Width = 57
              Height = 24
              Alignment = taRightJustify
              Lines.Strings = (
                '0')
              TabOrder = 1
            end
            object column_header_units_parenthesis_checkbox: TAutoCheckBox
              Left = 5
              Top = 76
              Width = 692
              Height = 17
              Anchors = [akLeft, akTop, akRight]
              Caption = 
                'Units code/label text is bracketed with parentheses, I.e.  (kg/m' +
                '²)'
              TabOrder = 2
            end
          end
        end
        object column_headers_delineation_tabsheet: TTabSheet
          Caption = 'Delineation'
          ImageIndex = 1
        end
      end
      object Button1: TButton
        Left = 16
        Top = 586
        Width = 585
        Height = 25
        Anchors = [akLeft, akBottom]
        Caption = 
          'Attempt to glean column definitions from the example file using ' +
          'this column header layout (not yet implemented)'
        TabOrder = 1
      end
    end
    object tabsheet_columns: TTabSheet
      Caption = 'Columns'
      ImageIndex = 4
      object Label25: TLabel
        Left = 8
        Top = 8
        Width = 695
        Height = 33
        Anchors = [akLeft, akTop, akRight]
        AutoSize = False
        Caption = 
          'This format editor is intended for column formatted tabular data' +
          ', either in formatted text files, database or spreadsheet format' +
          's.'
        WordWrap = True
      end
      object Label26: TLabel
        Left = 8
        Top = 24
        Width = 605
        Height = 49
        AutoSize = False
        Caption = 
          'When defining a format to be used to import data it is not neces' +
          'sary to declare all the fields that exist or will exist in the t' +
          'able, nor the order of the fields. The database will be queried ' +
          'for the actual fields that are available during import.'
        WordWrap = True
      end
      object columns_carriage_control_note: TLabel
        Left = 88
        Top = 56
        Width = 521
        Height = 29
        AutoSize = False
        Caption = 
          'This format uses a FORTRAN/COBOL carriage control in character p' +
          'osition 0 this is referred to as column 0. Do not add this colum' +
          'n to the following list. All data columns start positions should' +
          ' be relative to position 1.'
        WordWrap = True
      end
      object Label13: TLabel
        Left = 0
        Top = 208
        Width = 89
        Height = 403
        Anchors = [akLeft, akTop, akBottom]
        AutoSize = False
        Caption = 
          'The UED import utility uses either the ID or name column to filt' +
          'er weather station data into separate UED files. There may be ID' +
          ' or Name fields or both.'
        WordWrap = True
      end
      object Button7: TButton
        Left = 0
        Top = 120
        Width = 81
        Height = 25
        Caption = 'Delete'
        TabOrder = 0
        OnClick = column_delete_button_onclick
      end
      object columns_listbox: TAutoContainerListBox
        Left = 88
        Top = 88
        Width = 257
        Height = 527
        Anchors = [akLeft, akTop, akBottom]
        ItemHeight = 13
        TabOrder = 1
        OnClick = columns_listbox_onclick
      end
      object Button5: TButton
        Left = 0
        Top = 88
        Width = 81
        Height = 25
        Caption = 'Add'
        TabOrder = 2
        OnClick = column_add_button_onclick
      end
      object column_up_down_button: TUpDown
        Left = 64
        Top = 152
        Width = 17
        Height = 49
        Hint = 'Use these buttons to change the order of column headers'
        Min = 0
        ParentShowHint = False
        Position = 0
        ShowHint = True
        TabOrder = 3
        Wrap = False
        OnClick = column_up_down_buttonClick
      end
      object column_scrollbox: TScrollBox
        Left = 344
        Top = 88
        Width = 371
        Height = 529
        HorzScrollBar.Visible = False
        Anchors = [akLeft, akTop, akRight, akBottom]
        TabOrder = 4
        Visible = False
      end
      object button_ID_column: TButton
        Left = 0
        Top = 152
        Width = 33
        Height = 25
        Hint = 'Select the current column as the ID field.'
        Caption = 'ID '
        ParentShowHint = False
        ShowHint = True
        TabOrder = 5
        OnClick = button_ID_columnClick
      end
      object edit_ID_column: TAutoInt16Edit
        Left = 32
        Top = 152
        Width = 25
        Height = 24
        Hint = 'ID column number (used by UED weather data import utility)'
        Alignment = taRightJustify
        Lines.Strings = (
          '0')
        ParentShowHint = False
        ShowHint = True
        TabOrder = 6
      end
      object button_name_column: TButton
        Left = 0
        Top = 176
        Width = 33
        Height = 25
        Hint = 'Select the current column as the name field.'
        Caption = 'Name'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 7
        OnClick = button_name_columnClick
      end
      object edit_name_column: TAutoInt16Edit
        Left = 32
        Top = 176
        Width = 25
        Height = 24
        Hint = 'Name column number (used by UED weather data import utility)'
        Alignment = taRightJustify
        Lines.Strings = (
          '0')
        ParentShowHint = False
        ShowHint = True
        TabOrder = 8
      end
    end
    object tabsheet_header_fields: TTabSheet
      Caption = 'Header fields'
      ImageIndex = 2
      object Label27: TLabel
        Left = 0
        Top = 558
        Width = 706
        Height = 49
        Anchors = [akLeft, akRight, akBottom]
        AutoSize = False
        Caption = 
          'Header fields are one or more scalar data items that may preceed' +
          ' that tabular data.  For example: description of the data, weath' +
          'er station name, latitude/longitude, elevation, create/update da' +
          'te.  '
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
      end
      object Label3: TLabel
        Left = 8
        Top = 72
        Width = 162
        Height = 419
        Anchors = [akLeft, akTop, akRight, akBottom]
        AutoSize = False
        Caption = 
          'If this format does not have header fields leave this blank. DO ' +
          'NOTconfuse header fields with column headers, or column labels.'
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
      end
      object header_field_add_button: TButton
        Left = 8
        Top = 8
        Width = 75
        Height = 25
        Caption = 'Add'
        TabOrder = 0
        OnClick = header_field_add_button_onclick
      end
      object header_fields_listbox: TAutoContainerListBox
        Left = 88
        Top = 0
        Width = 232
        Height = 495
        Anchors = [akLeft, akTop, akBottom]
        ItemHeight = 13
        TabOrder = 1
        OnClick = header_fields_listbox_onclick
      end
      object header_field_delete_button: TButton
        Left = 8
        Top = 40
        Width = 75
        Height = 25
        Caption = 'Delete'
        TabOrder = 2
        OnClick = header_field_delete_button_onclick
      end
      object header_fields_terminator_groupbox: TGroupBox
        Left = 0
        Top = 494
        Width = 706
        Height = 57
        Anchors = [akLeft, akRight, akBottom]
        TabOrder = 3
        object Label23: TLabel
          Left = 8
          Top = 16
          Width = 145
          Height = 33
          AutoSize = False
          Caption = 'Header terminator character ASCII code'
          WordWrap = True
        end
        object Label24: TLabel
          Left = 256
          Top = 8
          Width = 425
          Height = 41
          Anchors = [akLeft, akTop, akRight]
          AutoSize = False
          Caption = 
            'Some headers may be variable length terminated by a special char' +
            'acter.  (Enter 0 if there are no special character that terminat' +
            'es the header fields block)'
          WordWrap = True
        end
        object header_terminator_character_edit: TAutoInt16Edit
          Left = 160
          Top = 16
          Width = 70
          Height = 24
          Hint = 'Enter the ASCII code for the header_terminator'
          Alignment = taRightJustify
          Lines.Strings = (
            '0')
          ParentShowHint = False
          ShowHint = True
          TabOrder = 0
        end
      end
      object header_field_scrollbox: TScrollBox
        Left = 320
        Top = -1
        Width = 393
        Height = 500
        Anchors = [akLeft, akTop, akRight, akBottom]
        TabOrder = 4
        Visible = False
      end
    end
  end
  object sample_file_opendialog: TOpenDialog
    DefaultExt = '*'
    Title = 'Select a file that is in the format being defined'
    Left = 300
    Top = 80
  end
end
