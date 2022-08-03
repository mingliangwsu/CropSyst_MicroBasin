object delineation_layout_form: Tdelineation_layout_form
  Left = 470
  Top = 478
  Width = 524
  Height = 249
  Align = alClient
  Caption = 'Delineation layout'
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
    Width = 516
    Height = 215
    ActivePage = tabsheet_delimiting
    Align = alClient
    TabOrder = 0
    object tabsheet_delimiting: TTabSheet
      Caption = 'Delimiting'
      object Label1: TLabel
        Left = 264
        Top = 96
        Width = 221
        Height = 13
        Caption = ' (otherwise an empty column value is assumed)'
      end
      object column_delimit_mode_radiogroupbox: TAutoRadioGroup
        Left = 0
        Top = 0
        Width = 508
        Height = 73
        Align = alTop
        Caption = 'Column delimit mode'
        Items.Strings = (
          
            'Columns are intrinsic to the file format type (I.e. databases, s' +
            'preadsheets)'
          
            'Each column has a fixed width (for all data records) (I.e. FORTR' +
            'AN,COBOL).'
          
            'Columns are delimited by a special characters (I.e. BASIC, comma' +
            ', tab delimited)')
        TabOrder = 0
        OnClick = column_delimit_mode_radiogroupboxClick
      end
      object continuous_delimiter_checkbox: TAutoCheckBox
        Left = 240
        Top = 80
        Width = 228
        Height = 17
        Anchors = [akLeft, akTop, akRight]
        Caption = 'Consecutive delimiters treated as one'
        TabOrder = 1
      end
      object delimiter_groupbox: TGroupBox
        Left = 0
        Top = 73
        Width = 233
        Height = 114
        Hint = 'The ASCII code for the delimit character between columns)'
        Align = alLeft
        Caption = 'Treat the following characters as delimitors:'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 2
        object delimiter_space_checkbox: TAutoCheckBox
          Left = 16
          Top = 16
          Width = 97
          Height = 17
          Caption = 'Space'
          TabOrder = 0
        end
        object delimiter_tab_checkbox: TAutoCheckBox
          Left = 16
          Top = 38
          Width = 97
          Height = 17
          Caption = 'Tab'
          TabOrder = 1
        end
        object delimiter_comma_checkbox: TAutoCheckBox
          Left = 16
          Top = 60
          Width = 73
          Height = 17
          Caption = 'Comma'
          TabOrder = 2
        end
        object delimiter_other_checkbox: TAutoCheckBox
          Left = 96
          Top = 16
          Width = 129
          Height = 17
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Other ASCII code'
          TabOrder = 3
          OnClick = delimiter_other_checkboxClick
        end
        object delimiter_other_edit: TAutoInt16Edit
          Left = 112
          Top = 32
          Width = 70
          Height = 24
          Alignment = taRightJustify
          Lines.Strings = (
            '0')
          TabOrder = 4
        end
        object Button2: TButton
          Left = 96
          Top = 72
          Width = 129
          Height = 25
          Caption = 'Show character map (NYI)'
          TabOrder = 5
          Visible = False
        end
        object delimiter_semicolon_checkbox: TAutoCheckBox
          Left = 16
          Top = 80
          Width = 81
          Height = 17
          Caption = 'Semicolon'
          TabOrder = 6
        end
        object AdvCharacterSelector1: TAdvCharacterSelector
          Left = 192
          Top = 48
          Width = 23
          Height = 22
          TabOrder = 7
          AppearanceStyle = esOffice2003Classic
          Version = '1.3.5.1'
          AutoLoad = False
          AutoThemeAdapt = False
          BorderDownColor = 7021576
          BorderHotColor = clBlack
          ButtonsPerRow = 10
          Caption = 'A'
          Color = clBtnFace
          ColorDown = 11900292
          ColorHot = 14073525
          ColorDropDown = 16251129
          Characters = 'abcdefghijklmnopqrstuvwxyz'
          CharFont.Charset = DEFAULT_CHARSET
          CharFont.Color = clWindowText
          CharFont.Height = -11
          CharFont.Name = 'MS Sans Serif'
          CharFont.Style = []
          Glyph.Data = {
            76010000424D7601000000000000760000002800000020000000100000000100
            04000000000000010000130B0000130B00001000000000000000000000000000
            800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
            3333333333333333333333333333333333333333FFF33FFFFF33333300033000
            00333337773377777333333330333300033333337FF33777F333333330733300
            0333333377FFF777F33333333700000073333333777777773333333333033000
            3333333337FF777F333333333307300033333333377F777F3333333333703007
            33333333377F7773333333333330000333333333337777F33333333333300003
            33333333337777F3333333333337007333333333337777333333333333330033
            3333333333377333333333333333033333333333333733333333333333333333
            3333333333333333333333333333333333333333333333333333}
          Style = ssButton
        end
      end
    end
    object tabsheet_quotation: TTabSheet
      Caption = 'String quotation'
      ImageIndex = 1
      object text_quote_mode_radiogroup: TAutoRadioGroup
        Left = 0
        Top = 0
        Width = 508
        Height = 105
        Align = alTop
        Caption = 'Character string are quoted'
        Items.Strings = (
          'Not quoted'
          'With single quote characters (as in Pascal text file)'
          
            'With double quote characters (as in BASIC text files, or CSV fil' +
            'es)'
          'With single or double quotes I.e. '#39'a"b'#39', or "c'#39'd"')
        TabOrder = 0
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Section markers'
      ImageIndex = 2
      object Label2: TLabel
        Left = 8
        Top = 12
        Width = 27
        Height = 13
        Caption = 'Begin'
      end
      object Label3: TLabel
        Left = 8
        Top = 36
        Width = 19
        Height = 13
        Caption = 'End'
      end
      object Label4: TLabel
        Left = 8
        Top = 64
        Width = 497
        Height = 49
        Anchors = [akLeft, akTop, akRight]
        AutoSize = False
        Caption = 
          'Some formats block or nest sections, or indicate the begin and/o' +
          'r end of data with labels (I.e. BEGIN_DATA ... END_DATA).  It wi' +
          'll be assumed these markers are the only text on the line and wi' +
          'll be in the left most character column (so spreadsheet cell).'
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
      end
      object Label5: TLabel
        Left = 392
        Top = 8
        Width = 110
        Height = 49
        Anchors = [akTop, akRight]
        AutoSize = False
        Caption = 'Leave these blank if there are no such markers.'
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
      end
      object edit_begin_marker: TAutoStringEdit
        Left = 72
        Top = 8
        Width = 313
        Height = 21
        Anchors = [akLeft, akTop, akRight]
        TabOrder = 0
      end
      object edit_end_marker: TAutoStringEdit
        Left = 72
        Top = 32
        Width = 313
        Height = 21
        Anchors = [akLeft, akTop, akRight]
        TabOrder = 1
      end
    end
  end
end
