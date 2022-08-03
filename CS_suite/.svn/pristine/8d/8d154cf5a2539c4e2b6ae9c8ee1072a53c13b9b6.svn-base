object soil_convertor_form: Tsoil_convertor_form
  Left = 1055
  Top = 461
  Width = 561
  Height = 441
  Caption = 'CropSyst soil conversion utility'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label4: TLabel
    Left = 0
    Top = 0
    Width = 553
    Height = 25
    Align = alTop
    AutoSize = False
    Caption = 
      'This utility can be used to import soil data from various standa' +
      'rd soil parameter file formats to CropSyst soil parameter files.'
    Color = clInfoBk
    ParentColor = False
    WordWrap = True
  end
  object format_page_control: TPageControl
    Left = 0
    Top = 50
    Width = 553
    Height = 327
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'ICASA /  DSSAT /  IBSNAT /  WISE soil'
      object Label1: TLabel
        Left = 24
        Top = 24
        Width = 491
        Height = 25
        Anchors = [akLeft, akTop, akRight]
        AutoSize = False
        Caption = 
          'Use this option to import  soil data stored in ICASA format (inc' +
          'luding both new and old DSSAT and IBSNAT formats).'
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
      end
      object Label6: TLabel
        Left = 24
        Top = 120
        Width = 445
        Height = 13
        Caption = 
          'Press the [Select files and import] button, select the file cont' +
          'aining the ICASA formated data file'
        Color = clInfoBk
        ParentColor = False
      end
      object IBSNAT_import_button: TBitBtn
        Left = 24
        Top = 64
        Width = 257
        Height = 41
        Caption = 'Select files and import'
        TabOrder = 0
        OnClick = IBSNAT_import_button_onclick
        Glyph.Data = {
          76010000424D7601000000000000760000002800000020000000100000000100
          04000000000000010000130B0000130B00001000000000000000000000000000
          800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
          33333333333FFFFFFFFF333333000000000033333377777777773333330FFFFF
          FFF03333337F333333373333330FFFFFFFF03333337F3FF3FFF73333330F00F0
          00F03333F37F773777373330330FFFFFFFF03337FF7F3F3FF3F73339030F0800
          F0F033377F7F737737373339900FFFFFFFF03FF7777F3FF3FFF70999990F00F0
          00007777777F7737777709999990FFF0FF0377777777FF37F3730999999908F0
          F033777777777337F73309999990FFF0033377777777FFF77333099999000000
          3333777777777777333333399033333333333337773333333333333903333333
          3333333773333333333333303333333333333337333333333333}
        NumGlyphs = 2
      end
    end
    object chemflow_tabsheet: TTabSheet
      Caption = 'CHEMFLOW'
      ImageIndex = 1
      object Label2: TLabel
        Left = 80
        Top = 56
        Width = 96
        Height = 13
        Caption = 'Not yet implemented'
      end
    end
    object STATSGO: TTabSheet
      Caption = 'STATSGO'
      ImageIndex = 2
      object STATSGO_groupbox_database_found: TGroupBox
        Left = 0
        Top = 50
        Width = 545
        Height = 249
        Align = alClient
        Caption = 'STATSGO database found'
        TabOrder = 0
        Visible = False
        object STATSGO_radiobutton_aggregation_option: TRadioGroup
          Left = 2
          Top = 15
          Width = 541
          Height = 49
          Align = alTop
          Caption = 'Aggregation option'
          ItemIndex = 0
          Items.Strings = (
            'Extract map unit soil sequences'
            
              'Aggregate soil sequences in each map unit to create an aggregate' +
              'd representitive pseudosoil')
          TabOrder = 0
          OnClick = STATSGO_radiobutton_aggregation_optionClick
        end
        object STATSGO_radiobutton_mapunit_selection_mode: TRadioGroup
          Left = 2
          Top = 64
          Width = 541
          Height = 66
          Align = alTop
          Caption = 'Map unit selection'
          ItemIndex = 0
          Items.Strings = (
            'Process all map units'
            'Process a specific map unit (and all its components)'
            'Process a specific map unit component')
          TabOrder = 1
          OnClick = STATSGO_radiobutton_mapunit_selection_modeClick
        end
        object STATSGO_groupbox_datum_selection: TGroupBox
          Left = 2
          Top = 130
          Width = 541
          Height = 73
          Align = alTop
          Caption = 'Datum selection'
          TabOrder = 2
          object STATSGO_groupbox_mapunit: TGroupBox
            Left = 8
            Top = 16
            Width = 177
            Height = 49
            Caption = 'Selecting a specific map unit'
            TabOrder = 0
            object STATSGO_label_mapunit: TLabel
              Left = 8
              Top = 20
              Width = 92
              Height = 13
              Caption = 'Map unit ID (MUID)'
            end
            object STATSGO_edit_mapunit: TEdit
              Left = 112
              Top = 16
              Width = 57
              Height = 21
              Anchors = [akLeft, akTop, akRight]
              TabOrder = 0
              Text = 'WA001'
            end
          end
          object STATSGO_sequence_groupbox: TGroupBox
            Left = 192
            Top = 16
            Width = 241
            Height = 49
            Caption = 'Map unit found, selecting specific soil sequence'
            TabOrder = 1
            object STATSGO_sequence_label: TLabel
              Left = 16
              Top = 20
              Width = 87
              Height = 13
              Caption = 'Sequence number'
            end
            object edit_STATSGO_sequence: TEdit
              Left = 112
              Top = 16
              Width = 33
              Height = 21
              TabOrder = 0
              Text = '0'
              OnExit = STATSGO_sequence_edit_onexit
            end
          end
        end
        object STATSGO_button_convert: TButton
          Left = 8
          Top = 210
          Width = 233
          Height = 25
          Caption = 'Perform conversion'
          TabOrder = 3
          OnClick = STATSGO_button_convertClick
        end
      end
      object panel_statsgo_folder: TPanel
        Left = 0
        Top = 0
        Width = 545
        Height = 25
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Select folder containing STATSGO database'
        TabOrder = 1
        object STATSGO_directory_edit: TAdvDirectoryEdit
          Left = 223
          Top = 2
          Width = 314
          Height = 21
          Flat = False
          LabelFont.Charset = DEFAULT_CHARSET
          LabelFont.Color = clWindowText
          LabelFont.Height = -11
          LabelFont.Name = 'MS Sans Serif'
          LabelFont.Style = []
          Lookup.Separator = ';'
          Anchors = [akLeft, akTop, akRight]
          Color = clWindow
          Enabled = True
          ReadOnly = False
          TabOrder = 0
          Text = 'C:\Simulation\Database\STATSGO\ArcInfo'
          Visible = True
          OnChange = STATSGO_directory_editChange
          Version = '1.3.2.3'
          ButtonStyle = bsButton
          ButtonWidth = 18
          Etched = False
          Glyph.Data = {
            CE000000424DCE0000000000000076000000280000000C0000000B0000000100
            0400000000005800000000000000000000001000000000000000000000000000
            8000008000000080800080000000800080008080000080808000C0C0C0000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00F00000000FFF
            00000088888880FF00000B088888880F00000BB08888888000000BBB00000000
            00000BBBBBBB0B0F00000BBB00000B0F0000F000BBBBBB0F0000FF0BBBBBBB0F
            0000FF0BBB00000F0000FFF000FFFFFF0000}
          BrowseDialogText = 'Select Directory'
        end
      end
      object panel_select_state: TPanel
        Left = 0
        Top = 25
        Width = 545
        Height = 25
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Select state'
        TabOrder = 2
        object STATSGO_edit_state: TEdit
          Left = 104
          Top = 2
          Width = 33
          Height = 21
          TabOrder = 0
          Text = 'WA'
          OnChange = STATSGO_directory_editChange
        end
      end
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 25
    Width = 553
    Height = 25
    Hint = 'Normally this will be a CropSyst parameter database soil folder.'
    Align = alTop
    Alignment = taLeftJustify
    BevelOuter = bvNone
    Caption = 'Destination folder'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 1
    object destitation_directory_edit: TAdvDirectoryEdit
      Left = 96
      Top = 2
      Width = 379
      Height = 21
      Hint = 'Normally this will be a CropSyst parameter database soil folder.'
      Flat = False
      FocusColor = clWindow
      LabelFont.Charset = DEFAULT_CHARSET
      LabelFont.Color = clWindowText
      LabelFont.Height = -11
      LabelFont.Name = 'MS Sans Serif'
      LabelFont.Style = []
      Lookup.Separator = ';'
      Anchors = [akLeft, akTop, akRight, akBottom]
      Color = clWindow
      Enabled = True
      ParentShowHint = False
      ReadOnly = False
      ShowHint = True
      TabOrder = 0
      Text = 'C:\Simulation\Database\Soil'
      Visible = True
      OnChange = destitation_directory_edit_onchange
      Version = '1.3.2.3'
      ButtonStyle = bsButton
      ButtonWidth = 18
      Etched = False
      Glyph.Data = {
        CE000000424DCE0000000000000076000000280000000C0000000B0000000100
        0400000000005800000000000000000000001000000000000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00F00000000FFF
        00000088888880FF00000B088888880F00000BB08888888000000BBB00000000
        00000BBBBBBB0B0F00000BBB00000B0F0000F000BBBBBB0F0000FF0BBBBBBB0F
        0000FF0BBB00000F0000FFF000FFFFFF0000}
      BrowseDialogText = 'Select Directory'
    end
    object button_explore: TBitBtn
      Left = 474
      Top = 0
      Width = 75
      Height = 25
      Anchors = [akTop, akRight, akBottom]
      Caption = 'Explore'
      TabOrder = 1
      OnClick = button_exploreClick
      Glyph.Data = {
        C6050000424DC605000000000000360400002800000014000000140000000100
        08000000000090010000120B0000120B00000001000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000C0DCC000F0CA
        A6000020400000206000002080000020A0000020C0000020E000004000000040
        20000040400000406000004080000040A0000040C0000040E000006000000060
        20000060400000606000006080000060A0000060C0000060E000008000000080
        20000080400000806000008080000080A0000080C0000080E00000A0000000A0
        200000A0400000A0600000A0800000A0A00000A0C00000A0E00000C0000000C0
        200000C0400000C0600000C0800000C0A00000C0C00000C0E00000E0000000E0
        200000E0400000E0600000E0800000E0A00000E0C00000E0E000400000004000
        20004000400040006000400080004000A0004000C0004000E000402000004020
        20004020400040206000402080004020A0004020C0004020E000404000004040
        20004040400040406000404080004040A0004040C0004040E000406000004060
        20004060400040606000406080004060A0004060C0004060E000408000004080
        20004080400040806000408080004080A0004080C0004080E00040A0000040A0
        200040A0400040A0600040A0800040A0A00040A0C00040A0E00040C0000040C0
        200040C0400040C0600040C0800040C0A00040C0C00040C0E00040E0000040E0
        200040E0400040E0600040E0800040E0A00040E0C00040E0E000800000008000
        20008000400080006000800080008000A0008000C0008000E000802000008020
        20008020400080206000802080008020A0008020C0008020E000804000008040
        20008040400080406000804080008040A0008040C0008040E000806000008060
        20008060400080606000806080008060A0008060C0008060E000808000008080
        20008080400080806000808080008080A0008080C0008080E00080A0000080A0
        200080A0400080A0600080A0800080A0A00080A0C00080A0E00080C0000080C0
        200080C0400080C0600080C0800080C0A00080C0C00080C0E00080E0000080E0
        200080E0400080E0600080E0800080E0A00080E0C00080E0E000C0000000C000
        2000C0004000C0006000C0008000C000A000C000C000C000E000C0200000C020
        2000C0204000C0206000C0208000C020A000C020C000C020E000C0400000C040
        2000C0404000C0406000C0408000C040A000C040C000C040E000C0600000C060
        2000C0604000C0606000C0608000C060A000C060C000C060E000C0800000C080
        2000C0804000C0806000C0808000C080A000C080C000C080E000C0A00000C0A0
        2000C0A04000C0A06000C0A08000C0A0A000C0A0C000C0A0E000C0C00000C0C0
        2000C0C04000C0C06000C0C08000C0C0A000F0FBFF00A4A0A000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFF07001B00FFFFFFFF2D2D2D2D2D2D2D2D2D2D
        2D2D009898002D2D2DFF2DFB282828281818281807001B98185A5A5A2DFF2DFB
        1828180707070707079898322A2818182DFF2DFB28180007000007A41B003232
        2A181A2A2DFF2DFB180007FEFEFEFE000007AA6AAA2A2A1A2DFF2DFB1800FEFE
        FEFEFEFE00A4F375AAFEFEFE2DFF2DFB0007FEFEFEFEFEFE0700BB75F2FEFEFE
        2DFF2DFB0007FEFEFEFEFEFE0700F2B3FEFEFEFE2DFF2DFB0007FEFFFFFEFEFE
        0700FEB0FEFEFEFE2DFF2DFBFE0707FEFFFEFE0707FEA8FEFEFEFEFE2DFF2DFB
        FEFE0007FEFE07009898985098FEFEFE2DFF2DFBFEFEFE00000000A850FE9850
        50FEFEFE2DFF2DFBFEFEFEFEFEFEFEFEFEFEFEFEF0FEFEFE2DFF2DFBFBFBFBFB
        FBFBFBFBFBFBFBFBFBFBFBFB2DFF2DFBFBFBFBFBFBFBFB2D2D2D2D2D2D2D2D2D
        2DFFFF2DFBFBFBFBFBFB2DFFFFFFFFFFFFFFFFFFFFFFFFFF2D2D2D2D2D2DFFFF
        FFFFFFFFFFFFFFFFFFFF}
    end
  end
  object panel_bottom: TPanel
    Left = 0
    Top = 377
    Width = 553
    Height = 30
    Align = alBottom
    BevelOuter = bvNone
    Caption = 'panel_bottom'
    TabOrder = 2
    object Label5: TLabel
      Left = 72
      Top = 0
      Width = 481
      Height = 30
      AutoSize = False
      Caption = 
        'Specify the target directory to store the converted soil paramet' +
        'er files. Then select the tab for the format to convert from, an' +
        'd follow the directions for that format conversion. Click [Explo' +
        're] to view generated files.'
      Color = clInfoBk
      ParentColor = False
      WordWrap = True
    end
    object close_button: TBitBtn
      Left = 8
      Top = 4
      Width = 75
      Height = 25
      TabOrder = 0
      Kind = bkClose
    end
  end
  object ICASA_file_open: TOpenDialog
    DefaultExt = 'SOL'
    Filter = 
      'IBSNAT soil file|*.SOL|IBSNAT formatted file (containing soil un' +
      'its)|*.*'
    Left = 36
    Top = 240
  end
end
