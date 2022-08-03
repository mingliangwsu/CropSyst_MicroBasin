object column_field_form: Tcolumn_field_form
  Left = 524
  Top = 97
  Width = 424
  Height = 425
  Caption = 'Column field'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 416
    Height = 391
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'Designation'
      object PageControl2: TPageControl
        Left = 0
        Top = 0
        Width = 408
        Height = 363
        ActivePage = TabSheet6
        Align = alClient
        TabOrder = 0
        object TabSheet6: TTabSheet
          Caption = 'Caption'
          object column_caption_edit: TAutoStringEdit
            Left = 4
            Top = 4
            Width = 395
            Height = 21
            Hint = 
              'This is the column header text as it will appear in text files a' +
              'nd spreadsheets. Enter the text in SDF format.'
            Anchors = [akLeft, akTop, akRight]
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
            Text = 'column_caption_edit'
          end
          object Memo3: TMemo
            Left = 0
            Top = 30
            Width = 392
            Height = 303
            Anchors = [akLeft, akTop, akRight, akBottom]
            Color = clInfoBk
            Lines.Strings = (
              'Enter the text that would appear in the column header '
              '(case senstive) as it appears in the file format. '
              ''
              'Although the caption is not used for database tables, '
              'you may want to provide this more descriptive form of '
              'text for other conversions and further documentation.'
              ''
              'If the caption spans multiple lines in text files,'
              'or multiple cells in a worksheet;'
              'enter the text in System Data Format, I.e.:  '
              '"This","is the","caption"'
              ''
              'It in not necessary to put quotation marks in '
              'the caption  unless you are using System Data Format.'
              ''
              'Note that in spreadsheets, column header text may'
              'actually be in a single cell, but may be displayed'
              'in more than one row or adjacent vertical cells.'
              'In this case, simply enter the text string I.e.'
              'This is the caption'
              ''
              'For text files that have no column headers.'
              'Even though the caption text is ignored,'
              'It is strongly recommended that you do give here a'
              'detailed description of the field/column.')
            ScrollBars = ssBoth
            TabOrder = 1
          end
        end
        object TabSheet7: TTabSheet
          Caption = 'Attribute/Label/Field'
          ImageIndex = 1
          object column_label_edit: TAutoStringEdit
            Left = 4
            Top = 4
            Width = 516
            Height = 21
            Hint = 'This is the attribute name for database tables.'
            Anchors = [akLeft, akTop, akRight]
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
            Text = 'column_label_edit'
            OnChange = column_label_edit_onchange
          end
          object Memo2: TMemo
            Left = 0
            Top = 30
            Width = 513
            Height = 303
            Anchors = [akLeft, akTop, akRight, akBottom]
            Color = clInfoBk
            ScrollBars = ssBoth
            TabOrder = 1
          end
        end
        object TabSheet8: TTabSheet
          Caption = 'Preferred units label'
          ImageIndex = 2
          object column_units_description_edit: TAutoStringEdit
            Left = 4
            Top = 4
            Width = 456
            Height = 21
            Anchors = [akLeft, akTop, akRight]
            TabOrder = 0
            Text = 'column_units_description_edit'
          end
          object Memo1: TMemo
            Left = 0
            Top = 30
            Width = 453
            Height = 303
            Anchors = [akLeft, akTop, akRight, akBottom]
            Color = clInfoBk
            Enabled = False
            ScrollBars = ssBoth
            TabOrder = 1
          end
        end
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Variable'
      ImageIndex = 2
      object label_variable: TLabel
        Left = 8
        Top = 24
        Width = 90
        Height = 13
        Caption = 'UED variable code'
      end
      object Label14: TLabel
        Left = 8
        Top = 48
        Width = 51
        Height = 13
        Caption = 'Units code'
      end
      object Label10: TLabel
        Left = 8
        Top = 80
        Width = 389
        Height = 65
        Anchors = [akLeft, akTop, akRight]
        AutoSize = False
        Caption = 
          'Mark "Record'#39's date" if this column is either the full date (in ' +
          'any format) I.e. YYYY/MM/DD MM/DD/YYYY or YYYYDDD, etc..  OR if ' +
          'this column is one of the subfields of the date (I.e. year, mont' +
          'h, DOM, or DOY).  Make sure to select the respecitve date units'
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
      end
      object column_UED_variable_code_combobox: TComboBox
        Left = 104
        Top = 24
        Width = 294
        Height = 21
        Hint = 'Enter the UED code in hexidecimal, or selected a defined code.'
        Anchors = [akLeft, akTop, akRight]
        ItemHeight = 13
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        Text = 'column_UED_variable_code_combobox'
        OnChange = column_UED_variable_code_comboboxChange
        Items.Strings = (
          '0x0  Unknown'
          '0x5820001 precipitation (liquid equivelent)'
          '0x1870001 avg. air temperature'
          '0x2870001 max. air temperature'
          '0x3870001 min. air temperature'
          '0x0870001 observed (instantaneous) air temperature'
          '0x1870002 avg. dew pt. temperature'
          '0x2870002 max. dew pt. temperature'
          '0x3870002 min. dew pt. temperature'
          '0x1830001 avg. relative_humidity'
          '0x2830001 max. relative humidity'
          '0x3830001 min. relative_humidity'
          '0x1860201 solar radiation'
          '0x1a20001 wind speed'
          '0x1a20002 wind direction'
          '0x5830003 pot.evapotranspiration'
          '0x5830002 act.evapotranspiration'
          '0x5830402 pan evaporation'
          '0x5830004 ref.evapotranspiration Penman-Monteith'
          '0x5830005 ref.evapotranspiration Priestly-Taylor'
          '0x5830006 ref.evapotranspiration Hargraves'
          '0x1830601 daytime vapor pressure deficit'
          '0x1830601 fullday vapor pressure deficit'
          '0x2830601 vapor pressure deficit'
          '0x1830010 cloud cover'
          '0x5820002 snow fall'
          '0x0820003 snow depth')
      end
      object column_units_code_button: TAutoUnitsButton
        Left = 104
        Top = 48
        Width = 294
        Height = 25
        Anchors = [akLeft, akTop, akRight]
        Caption = 'Units'
        TabOrder = 1
      end
      object records_date_checkbox: TAutoCheckBox
        Left = 8
        Top = 2
        Width = 389
        Height = 17
        Hint = 
          'Set to true if this column stores the record'#39's date or part of i' +
          't (I.e. the year, day, month, day of year).'
        Anchors = [akLeft, akTop, akRight]
        Caption = 'Record'#39's date (only for the time series date fields)'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 2
        OnClick = records_date_checkboxClick
      end
      object GroupBox1: TGroupBox
        Left = 8
        Top = 144
        Width = 389
        Height = 218
        Anchors = [akLeft, akTop, akRight, akBottom]
        Caption = 'Period level'
        TabOrder = 3
        object column_label_period: TLabel
          Left = 8
          Top = 24
          Width = 26
          Height = 13
          Caption = 'Level'
        end
        object column_label_period_note: TLabel
          Left = 72
          Top = 17
          Width = 309
          Height = 193
          Anchors = [akLeft, akTop, akRight, akBottom]
          AutoSize = False
          Caption = 
            'This is used to print period description columns (i..e. the crop' +
            ' growth stage in CropSyst). Normally the period level is not app' +
            'licable to most formats.'
          Color = clInfoBk
          ParentColor = False
          WordWrap = True
        end
        object column_period_edit: TAutoInt16Edit
          Left = 44
          Top = 21
          Width = 25
          Height = 24
          Alignment = taRightJustify
          Lines.Strings = (
            '0')
          TabOrder = 0
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Data type'
      ImageIndex = 1
      object radiogroup_column_data_type: TAutoRadioGroup
        Left = 0
        Top = 0
        Width = 97
        Height = 363
        Align = alLeft
        Caption = 'Data type'
        Items.Strings = (
          '<reserved>'
          'natural 8bit'
          'natural 16bit '
          'natural 32bit'
          'integer 8bit '
          'integer 16bit'
          'integer 32bit'
          'float 32bit'
          'float 64bit'
          'date'
          'time'
          'date and time')
        TabOrder = 0
        OnClick = radiogroup_column_data_typeClick
      end
      object panel_datatype: TPanel
        Left = 240
        Top = 0
        Width = 185
        Height = 289
        BevelOuter = bvNone
        TabOrder = 1
      end
      object scrollbox_datatype: TScrollBox
        Left = 97
        Top = 0
        Width = 311
        Height = 363
        Align = alClient
        TabOrder = 2
        object Label15: TLabel
          Left = 0
          Top = 0
          Width = 307
          Height = 48
          Anchors = [akLeft, akTop, akRight]
          AutoSize = False
          Caption = 
            'Data type specifies how data will be stored in binary files (I.e' +
            '. UED, dBase and Excel).'
          Color = clInfoBk
          ParentColor = False
          WordWrap = True
        end
        object Label11: TLabel
          Left = 0
          Top = 48
          Width = 307
          Height = 41
          Anchors = [akLeft, akTop, akRight]
          AutoSize = False
          Caption = 
            'Currently String, Date, Time, any of the integer and Float32 sho' +
            'uld be used.'
          Color = clInfoBk
          ParentColor = False
          WordWrap = True
        end
        object Label23: TLabel
          Left = 0
          Top = 89
          Width = 307
          Height = 48
          Anchors = [akLeft, akTop, akRight]
          AutoSize = False
          Caption = 
            'If date and time are stored in a single field/column, then use t' +
            'he Time data type.'
          Color = clInfoBk
          ParentColor = False
          WordWrap = True
        end
        object groupbox_precision: TGroupBox
          Left = 0
          Top = 137
          Width = 307
          Height = 105
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Precision'
          TabOrder = 0
          object Label4: TLabel
            Left = 2
            Top = 40
            Width = 303
            Height = 63
            Align = alBottom
            AutoSize = False
            Caption = 
              'Precision is the preferred number of digits following the decima' +
              'l point.  Required for text files with fixed width columns (I.e.' +
              ' formatted for FORTRAN).  Required when generating dBase tables.' +
              '  Recommended (but not required) when generating spreadsheets.'
            Color = clInfoBk
            ParentColor = False
            WordWrap = True
          end
          object column_precision_edit: TAutoInt16Edit
            Left = 8
            Top = 16
            Width = 41
            Height = 21
            Hint = 'The number of digits to show after the decimal point.'
            Alignment = taRightJustify
            Lines.Strings = (
              '0')
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
            OnExit = column_precision_editExit
          end
        end
        object GroupBox2: TGroupBox
          Left = 0
          Top = 242
          Width = 307
          Height = 49
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Missing value marker'
          TabOrder = 1
          object missing_value_edit: TAutoStringEdit
            Left = 8
            Top = 20
            Width = 291
            Height = 21
            Hint = 
              'This is text or number value that appears in the column field wh' +
              'en the value is missing.'
            Anchors = [akLeft, akTop, akRight]
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
          end
        end
      end
    end
    object tabsheet_fixed_width: TTabSheet
      Caption = 'Fixed width'
      ImageIndex = 4
      object Label7: TLabel
        Left = 8
        Top = 8
        Width = 22
        Height = 13
        Caption = 'Start'
      end
      object Label8: TLabel
        Left = 104
        Top = 0
        Width = 288
        Height = 73
        Anchors = [akLeft, akTop, akRight]
        AutoSize = False
        Caption = 
          'If the table columns are delimited by a character, use -1, other' +
          'wise enter the character column the field column starts in. For ' +
          'text files this is the character position (1 based). For spreads' +
          'heets this is the cell column (1 based) .'
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
      end
      object Label9: TLabel
        Left = 8
        Top = 72
        Width = 28
        Height = 13
        Caption = 'Width'
      end
      object Label12: TLabel
        Left = 104
        Top = 72
        Width = 288
        Height = 73
        Anchors = [akLeft, akTop, akRight]
        AutoSize = False
        Caption = 
          'For text files with fixed column widths, this is the number of c' +
          'haracters reserved for this column.  For database tables, this i' +
          's the width of the field in characters.'
        Color = clInfoBk
        ParentColor = False
        ParentShowHint = False
        ShowHint = True
        WordWrap = True
      end
      object column_start_edit: TAutoInt16Edit
        Left = 56
        Top = 8
        Width = 41
        Height = 21
        Alignment = taRightJustify
        Lines.Strings = (
          '0')
        TabOrder = 0
      end
      object column_width_edit: TAutoInt16Edit
        Left = 56
        Top = 72
        Width = 41
        Height = 21
        Hint = 
          'The number of characters of the fixed width column (Enter 0 for ' +
          'delimited text)'
        Alignment = taRightJustify
        Lines.Strings = (
          '0')
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        OnExit = column_width_editExit
      end
    end
    object TabSheet4: TTabSheet
      Caption = 'Advanced'
      ImageIndex = 3
      object PageControl3: TPageControl
        Left = 0
        Top = 0
        Width = 408
        Height = 363
        ActivePage = TabSheet9
        Align = alClient
        TabOrder = 0
        object TabSheet9: TTabSheet
          Caption = 'CropSyst'
          ImageIndex = 1
          object Label1: TLabel
            Left = 0
            Top = 0
            Width = 400
            Height = 33
            Align = alTop
            AutoSize = False
            Caption = 
              'These options are used in creating CropSyst report formats.  (Ig' +
              'nore these if you are not describing a CropSyst report format.'
            Color = clInfoBk
            ParentColor = False
            WordWrap = True
          end
          object Label17: TLabel
            Left = 88
            Top = 32
            Width = 304
            Height = 65
            Anchors = [akLeft, akTop, akRight]
            AutoSize = False
            Caption = 
              'Columns is used to read/write a set of values for UED dataset or' +
              ' vectors, starting in this column. Use -1 to indicate that this ' +
              'and all columns to the right are for the dataset/vector.'
            Color = clInfoBk
            ParentColor = False
            WordWrap = True
          end
          object Label16: TLabel
            Left = 16
            Top = 32
            Width = 40
            Height = 13
            Caption = 'Columns'
          end
          object column_statistic_radios: TAutoRadioGroup
            Left = -5
            Top = 104
            Width = 397
            Height = 57
            Hint = 'This is intended for export formats only.'
            Anchors = [akLeft, akTop, akRight]
            Caption = 'Optional statistic computation for dataset (export only)'
            Columns = 3
            Items.Strings = (
              'Value'
              'Sum'
              'Count'
              'Mean'
              'StdDev'
              'CoefVar')
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
          end
          object column_columns_edit: TAutoInt16Edit
            Left = 40
            Top = 72
            Width = 41
            Height = 24
            Alignment = taRightJustify
            Lines.Strings = (
              '0')
            TabOrder = 1
          end
          object column_spread_over_columns_checkbox: TAutoCheckBox
            Left = 24
            Top = 48
            Width = 57
            Height = 17
            Caption = 'Spread'
            TabOrder = 2
          end
        end
      end
    end
    object tabsheet_sheet: TTabSheet
      Caption = 'Sheet'
      ImageIndex = 5
      object groupbox_column_sheet_name: TGroupBox
        Left = 0
        Top = 73
        Width = 408
        Height = 129
        Align = alTop
        Caption = 'Sheet the column appears on'
        TabOrder = 0
        object Label24: TLabel
          Left = 2
          Top = 42
          Width = 404
          Height = 28
          Align = alBottom
          AutoSize = False
          Caption = 'For workbooks a column may be placed on any worksheet. '
          Color = clInfoBk
          ParentColor = False
          WordWrap = True
        end
        object Label2: TLabel
          Left = 2
          Top = 70
          Width = 404
          Height = 57
          Align = alBottom
          AutoSize = False
          Caption = 
            'The sheet name may be omitted if there is only one sheet or all ' +
            'sheets containing detail lines data has the same column format (' +
            'column headers, units, and detail lines start on the same rows o' +
            'n each sheet).'
          Color = clInfoBk
          ParentColor = False
          WordWrap = True
        end
        object edit_column_sheet_name: TAutoStringEdit
          Left = 8
          Top = 16
          Width = 392
          Height = 21
          Anchors = [akLeft, akTop, akRight]
          TabOrder = 0
        end
      end
      object groupbox_column_number: TGroupBox
        Left = 0
        Top = 0
        Width = 408
        Height = 73
        Align = alTop
        Caption = 'Column number'
        TabOrder = 1
        object Label3: TLabel
          Left = 2
          Top = 43
          Width = 404
          Height = 28
          Align = alBottom
          AutoSize = False
          Caption = 
            'Hint In Excel, columns can be numbered instead of labeled alphab' +
            'etically: Tools/Options/General/R1C1 reference style.'
          Color = clInfoBk
          ParentColor = False
          WordWrap = True
        end
        object Label5: TLabel
          Left = 88
          Top = 15
          Width = 318
          Height = 28
          Anchors = [akLeft, akTop, akRight]
          AutoSize = False
          Caption = 
            'In Excel, columns are labeled alphabetically by default.  Enter ' +
            'the corresponding numbers A=1, B=2,...IV=256. '
          Color = clInfoBk
          ParentColor = False
          WordWrap = True
        end
        object edit_column_number: TAutoInt16Edit
          Left = 8
          Top = 16
          Width = 70
          Height = 24
          Alignment = taRightJustify
          Lines.Strings = (
            '0')
          TabOrder = 0
        end
      end
    end
  end
end
