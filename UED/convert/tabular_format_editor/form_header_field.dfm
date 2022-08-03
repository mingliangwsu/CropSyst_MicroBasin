object header_field_form: Theader_field_form
  Left = 61
  Top = 623
  Width = 583
  Height = 212
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
    Width = 575
    Height = 178
    ActivePage = tabsheet_description
    Align = alClient
    TabOrder = 0
    object tabsheet_description: TTabSheet
      Caption = 'Description'
      object header_description_edit: TAutoStringEdit
        Left = 0
        Top = 0
        Width = 567
        Height = 21
        Hint = 'Description'
        Anchors = [akLeft, akTop, akRight]
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        OnExit = header_description_editChange
      end
      object header_data_radio: TAutoRadioGroup
        Left = 0
        Top = 28
        Width = 567
        Height = 122
        Anchors = [akLeft, akTop, akRight, akBottom]
        Caption = 'Header data'
        Items.Strings = (
          'Static text'
          'General comment'
          'Database description'
          'Generating application '
          'Location'
          'Scalar data (numeric)'
          'Time stamp')
        TabOrder = 1
        OnClick = header_data_radioClick
      end
    end
    object tabsheet_header_position: TTabSheet
      Caption = 'Position'
      ImageIndex = 1
      object header_field_position_worksheet_name_label: TLabel
        Left = 0
        Top = 0
        Width = 52
        Height = 13
        Caption = 'Worksheet'
      end
      object header_field_width_label: TLabel
        Left = 0
        Top = 28
        Width = 28
        Height = 13
        Caption = 'Width'
      end
      object header_row_label: TLabel
        Left = 168
        Top = 54
        Width = 22
        Height = 13
        Caption = 'Row'
      end
      object header_col_label: TLabel
        Left = 168
        Top = 76
        Width = 35
        Height = 13
        Caption = 'Column'
      end
      object header_static_text_label: TLabel
        Left = 0
        Top = 124
        Width = 47
        Height = 13
        Caption = 'Static text'
      end
      object header_field_width_note: TLabel
        Left = 112
        Top = 24
        Width = 455
        Height = 25
        Anchors = [akLeft, akTop, akRight]
        AutoSize = False
        Caption = 
          'Maximum number of characters. Enter 0 if the field ends at the e' +
          'nd of the line or terminator character is used.'
        WordWrap = True
      end
      object row_one_based_note: TLabel
        Left = 264
        Top = 104
        Width = 297
        Height = 13
        AutoSize = False
        Caption = 'one based'
        Color = clInfoBk
        ParentColor = False
      end
      object header_column_note: TLabel
        Left = 264
        Top = 52
        Width = 297
        Height = 29
        Anchors = [akLeft, akTop, akRight]
        AutoSize = False
        Caption = 
          'For spreadsheets it is the cell row number.  For text files it i' +
          's the line number (after any preamble)'
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
      end
      object header_row_note: TLabel
        Left = 264
        Top = 78
        Width = 297
        Height = 27
        Anchors = [akLeft, akTop, akRight]
        AutoSize = False
        Caption = 
          'For spreadsheets this is the cell column number (A=1). For text ' +
          'files this is the character position.'
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
      end
      object header_UED_scalar_precision_label: TLabel
        Left = 168
        Top = 100
        Width = 43
        Height = 13
        Caption = 'Precision'
      end
      object header_worksheet_name_edit: TAutoStringEdit
        Left = 64
        Top = 0
        Width = 503
        Height = 21
        Hint = 
          'Leave blank if the Excel file does not have worksheets. (may be ' +
          'left blank if only one worksheet).'
        Anchors = [akLeft, akTop, akRight]
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
      end
      object header_field_width: TAutoUint16Edit
        Left = 64
        Top = 24
        Width = 41
        Height = 24
        Alignment = taRightJustify
        Lines.Strings = (
          '0')
        TabOrder = 2
      end
      object header_field_row_edit: TAutoUint16Edit
        Left = 216
        Top = 50
        Width = 41
        Height = 21
        Alignment = taRightJustify
        Lines.Strings = (
          '0')
        TabOrder = 4
      end
      object header_field_column_edit: TAutoUint16Edit
        Left = 216
        Top = 74
        Width = 41
        Height = 21
        Alignment = taRightJustify
        Lines.Strings = (
          '0')
        TabOrder = 5
      end
      object header_static_text_edit: TAutoStringEdit
        Left = 64
        Top = 122
        Width = 503
        Height = 21
        Anchors = [akLeft, akTop, akRight]
        TabOrder = 7
        Text = 'header_static_text_edit'
      end
      object radiogroup_relative_to: TAutoRadioGroup
        Left = 8
        Top = 48
        Width = 153
        Height = 65
        Caption = 'Row relative'
        Items.Strings = (
          'Beginning of file'
          'Beginning of data (marker)'
          'Top of page (if paginated)')
        TabOrder = 3
      end
      object checkbox_on_every_page: TAutoCheckBox
        Left = 8
        Top = 8
        Width = 193
        Height = 17
        Caption = 'On every page'
        TabOrder = 1
      end
      object header_precision_edit: TAutoUint16Edit
        Left = 232
        Top = 98
        Width = 25
        Height = 21
        Alignment = taRightJustify
        Lines.Strings = (
          '0')
        TabOrder = 6
      end
    end
    object tabsheet_header_caption: TTabSheet
      Caption = 'Caption'
      ImageIndex = 2
      object Label3: TLabel
        Left = 0
        Top = 6
        Width = 22
        Height = 13
        Caption = 'Row'
      end
      object Label4: TLabel
        Left = 0
        Top = 32
        Width = 35
        Height = 13
        Caption = 'Column'
      end
      object caption_caption_label: TLabel
        Left = 0
        Top = 58
        Width = 36
        Height = 13
        Caption = 'Caption'
      end
      object Label2: TLabel
        Left = 192
        Top = 0
        Width = 369
        Height = 49
        Anchors = [akLeft, akTop, akRight]
        AutoSize = False
        Caption = 
          'Some times header fields have an associated static text label/ca' +
          'ption identifying the field.  This text is usually ignore when t' +
          'his format is used for import, but may be needed when exporting.'
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
      end
      object Label6: TLabel
        Left = 96
        Top = 0
        Width = 89
        Height = 57
        AutoSize = False
        Caption = 'Enter 0  in row and column to indicate no caption.'
        WordWrap = True
      end
      object caption_row_edit: TAutoUint16Edit
        Left = 48
        Top = 0
        Width = 41
        Height = 21
        Hint = 'Enter 0 if there is not associated caption.'
        Alignment = taRightJustify
        Lines.Strings = (
          '0')
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
      end
      object caption_col_edit: TAutoUint16Edit
        Left = 48
        Top = 28
        Width = 41
        Height = 21
        Hint = 'Enter 0 if there is not associated caption.'
        Alignment = taRightJustify
        Lines.Strings = (
          '0')
        TabOrder = 1
      end
      object caption_text_edit: TAutoStringEdit
        Left = 48
        Top = 56
        Width = 511
        Height = 21
        Anchors = [akLeft, akTop, akRight]
        TabOrder = 2
        Text = 'caption_text_edit'
      end
    end
    object tabsheet_header_UED_scalar: TTabSheet
      Caption = 'UED scalar'
      ImageIndex = 3
      object header_UED_scalar_record_code_label: TLabel
        Left = 0
        Top = 0
        Width = 62
        Height = 13
        Caption = 'Record code'
      end
      object header_UED_scalar_variable_label: TLabel
        Left = 0
        Top = 24
        Width = 65
        Height = 13
        Caption = 'Variable code'
      end
      object header_UED_scalar_units_label: TLabel
        Left = 0
        Top = 48
        Width = 51
        Height = 13
        Caption = 'Units code'
      end
      object header_UED_scalar_time_stamp_label: TLabel
        Left = 0
        Top = 80
        Width = 54
        Height = 13
        Caption = 'Time stamp'
      end
      object scalar_record_code_combobox: TAutoLabeledEnumComboBox
        Left = 72
        Top = 0
        Width = 495
        Height = 21
        Style = csDropDownList
        Anchors = [akLeft, akTop, akRight]
        ItemHeight = 0
        TabOrder = 0
      end
      object header_UED_variable_code_edit: TAutoInt16Edit
        Left = 72
        Top = 24
        Width = 495
        Height = 21
        Alignment = taRightJustify
        Anchors = [akLeft, akTop, akRight]
        Lines.Strings = (
          '0')
        TabOrder = 1
      end
      object header_units_button: TAutoUnitsButton
        Left = 72
        Top = 48
        Width = 495
        Height = 25
        Anchors = [akLeft, akTop, akRight]
        Caption = 'header_units_button'
        TabOrder = 2
      end
      object header_timestep_format_combobox: TAutoContainerComboBox
        Left = 72
        Top = 80
        Width = 495
        Height = 21
        Anchors = [akLeft, akTop, akRight]
        ItemHeight = 0
        TabOrder = 3
        Text = 'header_timestep_format_combobox'
      end
    end
    object tabsheet_header_UED_location_variable: TTabSheet
      Caption = 'UED location'
      ImageIndex = 4
      object location_variable_radios: TAutoRadioGroup
        Left = 0
        Top = 0
        Width = 567
        Height = 150
        Align = alClient
        Caption = 'Location variable'
        Items.Strings = (
          'Station ID'
          'Latitude (decimal degrees)'
          'Latitude (deg°min"sec'#39')'
          'Longitude (decimal degrees)'
          'Longitude (deg°min"sec'#39')'
          'Elevation (meters)'
          'Elevation (feet)'
          'Country name'
          'State name'
          'County name'
          'Description'
          'Station name'
          'Comment'
          'Station number')
        TabOrder = 0
      end
    end
    object tabsheet_header_UED_comment: TTabSheet
      Caption = 'UED comment'
      ImageIndex = 5
      object comment_index_label: TLabel
        Left = 8
        Top = 8
        Width = 49
        Height = 25
        AutoSize = False
        Caption = 'Comment index'
        WordWrap = True
      end
      object header_comment_index_edit: TAutoUint16Edit
        Left = 64
        Top = 8
        Width = 33
        Height = 21
        Alignment = taRightJustify
        Lines.Strings = (
          '0')
        TabOrder = 0
      end
    end
    object tabsheet_header_UED_description: TTabSheet
      Caption = 'UED description'
      ImageIndex = 6
      object description_index_label: TLabel
        Left = 8
        Top = 8
        Width = 53
        Height = 26
        Caption = 'Description index'
        WordWrap = True
      end
      object header_description_index_edit: TAutoUint16Edit
        Left = 64
        Top = 8
        Width = 33
        Height = 24
        Alignment = taRightJustify
        Lines.Strings = (
          '0')
        TabOrder = 0
      end
    end
    object tabsheet_header_UED_application: TTabSheet
      Caption = 'UED application'
      ImageIndex = 7
      object header_UED_application_note: TLabel
        Left = 104
        Top = 6
        Width = 457
        Height = 49
        Anchors = [akLeft, akTop, akRight]
        AutoSize = False
        Caption = 
          'A file may have an optional record the identifies the applicatio' +
          'n program that edited/produced/generated the data.'
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
      end
      object generating_application_variable_radios: TAutoRadioGroup
        Left = 0
        Top = 0
        Width = 97
        Height = 57
        Caption = 'Application'
        Items.Strings = (
          'version'
          'description')
        TabOrder = 0
      end
    end
  end
end
