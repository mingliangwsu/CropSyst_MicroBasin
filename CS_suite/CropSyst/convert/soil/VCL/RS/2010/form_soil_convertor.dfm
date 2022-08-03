object soil_convertor_form: Tsoil_convertor_form
  Left = 0
  Top = 0
  Caption = 'soil_convertor_form'
  ClientHeight = 484
  ClientWidth = 678
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label4: TLabel
    Left = 0
    Top = 0
    Width = 678
    Height = 25
    Align = alTop
    AutoSize = False
    Caption = 
      'This utility can be used to import soil data from various standa' +
      'rd soil parameter file formats to CropSyst soil parameter files.'
    Color = clInfoBk
    ParentColor = False
    Transparent = False
    WordWrap = True
    ExplicitWidth = 553
  end
  object Panel2: TPanel
    Left = 0
    Top = 25
    Width = 678
    Height = 25
    Hint = 'Normally this will be a CropSyst parameter database soil folder.'
    Align = alTop
    Alignment = taLeftJustify
    BevelOuter = bvNone
    Caption = 'Destination folder'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 0
    DesignSize = (
      678
      25)
    object destitation_directory_edit: TAdvDirectoryEdit
      Left = -354
      Top = 402
      Width = 504
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
      Version = '1.3.2.8'
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
      Left = 599
      Top = 0
      Width = 75
      Height = 25
      Anchors = [akTop, akRight, akBottom]
      Caption = 'Explore'
      DoubleBuffered = True
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
      ParentDoubleBuffered = False
      TabOrder = 1
      OnClick = button_exploreClick
    end
    object editdir_destination: TAdvDirectoryEdit
      Left = 89
      Top = -2
      Width = 504
      Height = 21
      Flat = False
      LabelFont.Charset = DEFAULT_CHARSET
      LabelFont.Color = clWindowText
      LabelFont.Height = -11
      LabelFont.Name = 'Tahoma'
      LabelFont.Style = []
      Lookup.Separator = ';'
      Anchors = [akLeft, akTop, akRight]
      Color = clWindow
      Enabled = True
      ReadOnly = False
      TabOrder = 2
      Visible = True
      OnChange = editdir_destinationChange
      Version = '1.3.2.8'
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
  object format_page_control: TPageControl
    Left = 0
    Top = 50
    Width = 678
    Height = 404
    ActivePage = tabsheet_STATSGO2
    Align = alClient
    TabOrder = 1
    object TabSheet1: TTabSheet
      Caption = 'ICASA /  DSSAT /  IBSNAT /  WISE soil'
      DesignSize = (
        670
        376)
      object Label1: TLabel
        Left = 24
        Top = 24
        Width = 616
        Height = 25
        Anchors = [akLeft, akTop, akRight]
        AutoSize = False
        Caption = 
          'Use this option to import  soil data stored in ICASA format (inc' +
          'luding both new and old DSSAT and IBSNAT formats).'
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
        ExplicitWidth = 491
      end
      object Label6: TLabel
        Left = 24
        Top = 120
        Width = 461
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
        DoubleBuffered = True
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
        ParentDoubleBuffered = False
        TabOrder = 0
        OnClick = IBSNAT_import_buttonClick
      end
    end
    object chemflow_tabsheet: TTabSheet
      Caption = 'CHEMFLOW'
      ImageIndex = 1
      object Label2: TLabel
        Left = 80
        Top = 56
        Width = 99
        Height = 13
        Caption = 'Not yet implemented'
      end
    end
    object tabsheet_STATSGO2: TTabSheet
      Caption = 'STATSGO2'
      ImageIndex = 2
      object ScrollBox1: TScrollBox
        Left = 0
        Top = 0
        Width = 670
        Height = 376
        Align = alClient
        TabOrder = 0
        object panel_statsgo_folder: TPanel
          Left = 0
          Top = 0
          Width = 666
          Height = 25
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Select the STATSGO2 mapunit.txt MS-Access import file'
          TabOrder = 0
          object edit_mapunit_txt: TAdvFileNameEdit
            Left = 272
            Top = 0
            Width = 394
            Height = 25
            Hint = 
              'This file will usually be found in gsmsoil_us\tabular directory ' +
              'after downloading and extracting the ZIP archive.'
            Flat = False
            LabelFont.Charset = DEFAULT_CHARSET
            LabelFont.Color = clWindowText
            LabelFont.Height = -11
            LabelFont.Name = 'Tahoma'
            LabelFont.Style = []
            Lookup.Separator = ';'
            Align = alRight
            Anchors = [akLeft, akTop, akRight, akBottom]
            Color = clWindow
            Enabled = True
            ParentShowHint = False
            ReadOnly = False
            ShowHint = True
            TabOrder = 0
            Text = 
              'C:\Simulation\Database\STATSGO2\gsmsoil_us\gsmsoil_us\tabular\ma' +
              'punit.txt'
            Visible = True
            OnChange = edit_mapunit_txtChange
            Version = '1.3.2.8'
            ButtonStyle = bsButton
            ButtonWidth = 18
            Etched = False
            Glyph.Data = {
              CE000000424DCE0000000000000076000000280000000C0000000B0000000100
              0400000000005800000000000000000000001000000000000000000000000000
              8000008000000080800080000000800080008080000080808000C0C0C0000000
              FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00D00000000DDD
              00000077777770DD00000F077777770D00000FF07777777000000FFF00000000
              00000FFFFFFF0DDD00000FFF00000DDD0000D000DDDDD0000000DDDDDDDDDD00
              0000DDDDD0DDD0D00000DDDDDD000DDD0000}
            Filter = 'mapunit.txt'
            FilterIndex = 0
            DialogOptions = []
            DialogKind = fdOpen
            ExplicitLeft = 273
          end
        end
        object groupbox_mapunix_selection: TGroupBox
          Left = 0
          Top = 25
          Width = 666
          Height = 88
          Align = alTop
          Caption = 'Map unit selection (leave blank to select all)'
          TabOrder = 1
          object Label3: TLabel
            Left = 2
            Top = 15
            Width = 662
            Height = 13
            Align = alTop
            Caption = 
              'Map units can be listed in a dBase .DBF format table with a fiel' +
              'd MUKEY'
            ExplicitWidth = 340
          end
          object Label7: TLabel
            Left = 2
            Top = 49
            Width = 662
            Height = 13
            Align = alTop
            Caption = 'and/or enter specific map unit keys to include'
            ExplicitWidth = 217
          end
          object filenameedit_DBF: TAdvFileNameEdit
            Left = 2
            Top = 28
            Width = 662
            Height = 21
            Flat = False
            LabelFont.Charset = DEFAULT_CHARSET
            LabelFont.Color = clWindowText
            LabelFont.Height = -11
            LabelFont.Name = 'Tahoma'
            LabelFont.Style = []
            Lookup.Separator = ';'
            Align = alTop
            Color = clWindow
            Enabled = True
            ReadOnly = False
            TabOrder = 0
            Text = 'P:\REACCH\database\soil\gridcell_lat_lon_MUKEY.dbf'
            Visible = True
            OnChange = filenameedit_DBFChange
            Version = '1.3.2.8'
            ButtonStyle = bsButton
            ButtonWidth = 18
            Etched = False
            Glyph.Data = {
              CE000000424DCE0000000000000076000000280000000C0000000B0000000100
              0400000000005800000000000000000000001000000000000000000000000000
              8000008000000080800080000000800080008080000080808000C0C0C0000000
              FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00D00000000DDD
              00000077777770DD00000F077777770D00000FF07777777000000FFF00000000
              00000FFFFFFF0DDD00000FFF00000DDD0000D000DDDDD0000000DDDDDDDDDD00
              0000DDDDD0DDD0D00000DDDDDD000DDD0000}
            Filter = '*.dbf'
            FilterIndex = 0
            DialogOptions = []
            DialogKind = fdOpen
            ExplicitLeft = 3
            ExplicitTop = 22
          end
          object edit_specific_mapunits: TEdit
            Left = 2
            Top = 62
            Width = 662
            Height = 21
            Align = alTop
            TabOrder = 1
            TextHint = 'Enter map unit keys (mukey) values delimited by spaces'
            OnChange = edit_specific_mapunitsChange
          end
        end
        object STATSGO_groupbox_database_found: TGroupBox
          Left = 0
          Top = 113
          Width = 666
          Height = 112
          Align = alTop
          Caption = 'STATSGO2 database found'
          TabOrder = 2
          Visible = False
          object STATSGO_radiobutton_aggregation_option: TRadioGroup
            Left = 2
            Top = 15
            Width = 662
            Height = 66
            Align = alTop
            Caption = 'Aggregation option'
            ItemIndex = 2
            Items.Strings = (
              'Extract map unit soil components'
              
                'Aggregate soil sequences in each map unit to create an aggregate' +
                'd representitive pseudopedon'
              'Use primary component as a representitive pedon')
            TabOrder = 0
          end
          object panel_STATSGO2_converting: TPanel
            Left = 2
            Top = 81
            Width = 662
            Height = 32
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Converting'
            TabOrder = 1
            object label_STATSGO2_curr_mukey: TLabel
              Left = 555
              Top = 0
              Width = 107
              Height = 32
              Align = alRight
              AutoSize = False
              ExplicitLeft = 520
              ExplicitTop = 6
              ExplicitHeight = 21
            end
            object checkbox_STATSGO2_continue: TCheckBox
              Left = 485
              Top = 0
              Width = 70
              Height = 32
              Align = alRight
              Caption = 'Continue'
              Checked = True
              State = cbChecked
              TabOrder = 1
            end
            object button_STATSGO2_convert: TButton
              Left = 0
              Top = 2
              Width = 121
              Height = 25
              Caption = 'Perform conversion'
              TabOrder = 0
              OnClick = button_STATSGO2_convertClick
            end
          end
        end
        object progress_bar: TProgressBar
          Left = 0
          Top = 225
          Width = 666
          Height = 24
          Align = alTop
          TabOrder = 3
        end
      end
    end
    object tabsheet_CanSIS_NSDB: TTabSheet
      Caption = 'CanSIS NSDB'
      ImageIndex = 3
      ExplicitTop = 26
      object Label8: TLabel
        Left = 0
        Top = 13
        Width = 670
        Height = 13
        Align = alTop
        Caption = 
          'Soil data available from: http://sis.agr.gc.ca/cansis/nsdb/dss/i' +
          'ndex.html'
        ExplicitWidth = 346
      end
      object Label9: TLabel
        Left = 0
        Top = 0
        Width = 670
        Height = 13
        Align = alTop
        Caption = 
          'Canadian Soil Information Service, National Soil Database  (Vers' +
          'ion 2 or Version 3)'
        ExplicitWidth = 393
      end
      object groupbox_CanSIS_soil_layer_table: TGroupBox
        Left = 0
        Top = 26
        Width = 670
        Height = 47
        Align = alTop
        Caption = 'Soil Layer Table'
        TabOrder = 0
        object filedit_CanSIS_NSDB: TAdvFileNameEdit
          Left = 2
          Top = 15
          Width = 666
          Height = 21
          Flat = False
          LabelFont.Charset = DEFAULT_CHARSET
          LabelFont.Color = clWindowText
          LabelFont.Height = -11
          LabelFont.Name = 'Tahoma'
          LabelFont.Style = []
          Lookup.Separator = ';'
          Align = alTop
          Color = clWindow
          Enabled = True
          ReadOnly = False
          TabOrder = 0
          Text = 
            'S:\Database\CanSIS_NSDB\SLC_3.2\British Columnbia\soil_layer_bc_' +
            'v2r20130705.dbf'
          Visible = True
          Version = '1.3.2.8'
          ButtonStyle = bsButton
          ButtonWidth = 18
          Etched = False
          Glyph.Data = {
            CE000000424DCE0000000000000076000000280000000C0000000B0000000100
            0400000000005800000000000000000000001000000000000000000000000000
            8000008000000080800080000000800080008080000080808000C0C0C0000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00D00000000DDD
            00000077777770DD00000F077777770D00000FF07777777000000FFF00000000
            00000FFFFFFF0DDD00000FFF00000DDD0000D000DDDDD0000000DDDDDDDDDD00
            0000DDDDD0DDD0D00000DDDDDD000DDD0000}
          Filter = '*.dbf'
          FilterIndex = 0
          DialogOptions = []
          DialogKind = fdOpen
          ExplicitWidth = 667
        end
      end
      object button_CanSIS_NSDB_convert: TButton
        Left = 3
        Top = 122
        Width = 121
        Height = 25
        Caption = 'Perform conversion'
        TabOrder = 1
        OnClick = button_CanSIS_NSDB_convertClick
      end
    end
  end
  object panel_bottom: TPanel
    Left = 0
    Top = 454
    Width = 678
    Height = 30
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 2
    object Label5: TLabel
      Left = 89
      Top = 0
      Width = 589
      Height = 30
      Align = alRight
      Anchors = [akLeft, akTop, akRight, akBottom]
      AutoSize = False
      Caption = 
        'Specify the target directory to store the converted soil paramet' +
        'er files. Then select the tab for the format to convert from, an' +
        'd follow the directions for that format conversion. Click [Explo' +
        're] to view generated files.'
      Color = clInfoBk
      ParentColor = False
      WordWrap = True
      ExplicitWidth = 554
    end
    object close_button: TBitBtn
      Left = 8
      Top = 4
      Width = 75
      Height = 25
      DoubleBuffered = True
      Kind = bkClose
      ParentDoubleBuffered = False
      TabOrder = 0
    end
  end
  object ICASA_file_open: TOpenDialog
    DefaultExt = 'SOL'
    Filter = 
      'IBSNAT soil file|*.SOL|IBSNAT formatted file (containing soil un' +
      'its)|*.*'
    Left = 476
    Top = 24
  end
end
