object sync_form: Tsync_form
  Left = 599
  Top = -377
  Width = 539
  Height = 343
  Caption = 'Syncronization'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDefaultPosOnly
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object sync_mode_pagecontrol: TPageControl
    Left = 0
    Top = 0
    Width = 531
    Height = 309
    ActivePage = fruit_tree_phenologic_tabsheet
    Align = alClient
    MultiLine = True
    Style = tsButtons
    TabOrder = 0
    OnChange = sync_mode_pagecontrol_onchange
    object fixed_date_tabsheet: TTabSheet
      Caption = 'Specific fixed date'
      ImageIndex = 3
      object fixed_date_note: TLabel
        Left = 8
        Top = 56
        Width = 507
        Height = 25
        Anchors = [akLeft, akTop, akRight]
        AutoSize = False
        Caption = 
          'Avoid using fixed dates for management that is associated with a' +
          ' crop in a rotation.'
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
      end
      object Label7: TLabel
        Left = 8
        Top = 88
        Width = 507
        Height = 25
        Anchors = [akLeft, akTop, akRight]
        AutoSize = False
        Caption = 
          'Specific dates can be used with period repetition, for successiv' +
          'e years, the dates will be recalculated.'
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
      end
      object actual_datebutton: TAutoDateButton
        Left = 8
        Top = 8
        Width = 507
        Height = 41
        Hint = 'Click here to set actual date'
        Anchors = [akLeft, akTop, akRight]
        Caption = 'actual_datebutton'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        Glyph.Data = {
          6E0E0000424D6E0E000000000000360000002800000022000000230000000100
          180000000000380E000000000000000000000000000000000000848284848284
          8482848482848482848482848482848482848482848482848482848482848482
          8484828484828484828484828484828484828484828484828484828484828484
          8284848284848284848284848284848284848284848284848284848284848284
          0000848284848284848284848284848284848284848284848284848284848284
          8482848482840000000000000000008482848482848482848482848482848482
          8484828484828484828484828484828484828484828484828484828484828484
          8284848284848284000084828484828484828484828484828484828484828484
          8284848284848284848284000000848284C6C3C6000000000000000000848284
          8482848482848482848482848482848482848482848482848482848482848482
          8484828484828484828484828484828400008482848482848482848482848482
          84848284848284848284848284848284848284000000C6C3C6FFFFFFFFFFFFC6
          C3C6000000000000000000848284848284848284848284848284848284848284
          8482848482848482848482848482848482848482848482840000848284848284
          848284848284848284848284848284848284848284848284000000848284C6C3
          C6FFFFFFC6C3C6FFFFFFFFFFFFC6C3C600000000000000000084828484828484
          8284848284848284848284848284848284848284848284848284848284848284
          0000848284848284848284848284848284848284848284848284848284848284
          000000C6C3C6FFFFFFFFFFFFC6C3C6FFFFFFC6C3C6FFFFFFFFFFFFC6C3C60000
          0000000000000084828484828484828484828484828484828484828484828484
          8284848284848284000084828484828484828484828484828484828484828484
          8284848284000000848284C6C3C6FFFFFFC6C3C6FFFFFFFFFFFFC6C3C6FFFFFF
          C6C3C6FFFFFFFFFFFFC6C3C60000000000000000008482848482848482848482
          8484828484828484828484828484828400008482848482848482848482848482
          84848284848284848284848284000000C6C3C6FFFFFFFFFFFFC6C3C6FFFFFFC6
          C3C6FFFFFFFFFFFFC6C3C6FFFFFFC6C3C6FFFFFFFFFFFFC6C3C6000000000000
          0000008482848482848482848482848482848482848482840000848284848284
          848284848284848284848284848284848284000000848284C6C3C6FFFFFFC6C3
          C6FFFFFFFFFFFFC6C3C6FFFFFFC6C3C6FFFFFFFFFFFFC6C3C6FFFFFFC6C3C6FF
          FFFFFFFFFFC6C3C6000000000000000000848284848284848284848284848284
          0000848284848284848284848284848284848284848284848284000000C6C3C6
          FFFFFFFFFFFFC6C3C6FFFFFFC6C3C6FFFFFFFFFFFFC6C3C6FFFFFFC6C3C6FFFF
          FFFFFFFFC6C3C6FFFFFFC6C3C6FFFFFFFFFFFFC6C3C600000000000000000084
          8284848284848284000084828484828484828484828484828484828484828400
          0000848284C6C3C6FFFFFFC6C3C6FFFFFFFFFFFFC6C3C6FFFFFFC6C3C6FFFFFF
          FFFFFFC6C3C6FFFFFFC6C3C6FFFFFFFFFFFFC6C3C6FFFFFFC6C3C6FFFFFFFFFF
          FFC6C3C600000000000084828484828400008482848482848482848482848482
          84848284848284000000C6C3C6FFFFFFFFFFFFC6C3C6FFFFFFC6C3C6FFFFFFFF
          FFFFC6C3C6FFFFFFC6C3C6FFFFFF000084000084000084C6C3C6FFFFFFFFFFFF
          C6C3C6FFFFFFC6C3C6FFFFFFC6C3C60000008482848482840000848284848284
          848284848284848284848284000000848284C6C3C6FFFFFFC6C3C6FFFFFFFFFF
          FFC6C3C6FFFFFFC6C3C6FFFFFFFFFFFFC6C3C6000084FFFFFFFFFFFFFFFFFF00
          0084C6C3C6C6C3C6FFFFFFFFFFFFC6C3C6FFFFFF000000848284848284848284
          0000848284848284848284848284848284848284000000C6C3C6FFFFFF840000
          840000C6C3C6C6C3C6FFFFFFFFFFFFC6C3C6FFFFFFC6C3C6FFFFFF000084FFFF
          FFFFFFFFFFFFFFFFFFFF000084C6C3C6FFFFFFC6C3C6FFFFFF00000084828484
          82848482848482840000848284848284848284848284848284000000848284C6
          C3C6FFFFFF840000840000840000840000C6C3C6C6C3C6FFFFFFFFFFFFC6C3C6
          FFFFFFC6C3C6000084FFFFFFFFFFFFFFFFFF000084FFFFFFFFFFFFC6C3C6FFFF
          FF00000084828484828484828484828400008482848482848482848482848482
          84000000848284848284848284FFFFFFFFFFFF840000840000840000840000C6
          C3C6C6C3C6FFFFFFFFFFFFC6C3C6FFFFFF000084000084000084C6C3C6FFFFFF
          C6C3C6FFFFFF0000008482848482848482848482848482840000848284848284
          848284848284848284848284000000C6C3C6C6C3C6848284848284FFFFFFFFFF
          FF840000840000848284848284C6C3C6C6C3C6FFFFFFFFFFFFC6C3C6FFFFFFC6
          C3C6FFFFFFFFFFFFC6C3C6FFFFFF000000848284848284848284848284848284
          0000848284848284848284848284848284848284000000FFFFFF008200C6C3C6
          C6C3C6848284848284FFFFFFFFFFFF848284848284848284848284C6C3C6C6C3
          C6FFFFFFFFFFFFC6C3C6FFFFFFC6C3C6FFFFFF00000084828484828484828484
          82848482848482840000848284848284848284848284848284000000C6C3C6FF
          FFFF008200008200008200C6C3C6C6C3C6848284848284FFFFFFFFFFFF848284
          848284848284848284C6C3C6C6C3C6FFFFFFFFFFFFC6C3C6FFFFFF0000008482
          8484828484828484828484828484828400008482848482848482848482848482
          84000000FFFFFFC6C3C6008200008200008200008200008200C6C3C6C6C3C684
          8284848284FFFFFFFFFFFF848284848284848284848284C6C3C6C6C3C6FFFFFF
          0000008482848482848482848482848482848482848482840000848284848284
          848284848284000000C6C3C6FFFFFF8482840082000082000082000082000082
          00008200008200C6C3C6C6C3C6848284848284FFFFFFFFFFFF84828484828484
          8284C6C3C6FFFFFF000000848284848284848284848284848284848284848284
          0000848284848284848284848284000000C6C3C6C6C3C6848284848200C6C3C6
          008200008200008200008200008200008200008200C6C3C6C6C3C68482848482
          84FFFFFFFFFFFF848284FFFFFF00000084828484828484828484828484828484
          82848482848482840000848284848284848284000000C6C3C6FFFFFFC6C3C6FF
          FF00848284848200C6C3C6008200008200008200008200008200008200008200
          008200C6C3C6C6C3C6848284848284FFFFFFFFFFFF0000008482848482848482
          848482848482848482848482848482840000848284848284000000C6C3C6FFFF
          FFC6C3C6FFFF00C6C3C6FFFFFFFFFFFFC6C3C600820000820000820000820000
          8200008200008200008200008200008200C6C3C6C6C3C6848284000000848284
          8482848482848482848482848482848482848482848482840000848284000000
          FFFFFFFFFFFFC6C3C6FFFF00C6C3C6FFFF00C6C3C6FFFF00C6C3C6FFFFFFFFFF
          FF008200008200008200008200008200008200008200008200008200008200C6
          C3C6000000848284848284848284848284848284848284848284848284848284
          0000848284848284000000000000FFFFFFFFFFFFFFFF00C6C3C6FFFF00C6C3C6
          FFFF00C6C3C6FFFFFFFFFFFFFFFFFF0082000082000082000082000082000082
          00008200008200FFFFFF00000084828484828484828484828484828484828484
          82848482848482840000848284848284848284848284000000000000FFFFFFFF
          FFFFC6C3C6FFFF00C6C3C6FFFF00FFFFFFFFFFFFFFFFFFFFFFFFC6C3C6C6C3C6
          C6C3C6008200008200008200008200FFFFFF0000008482848482848482848482
          8484828484828484828484828484828400008482848482848482848482848482
          84848284000000000000FFFFFFFFFFFFFFFF00C6C3C6FFFF00C6C3C6FFFF00C6
          C3C6FFFF00C6C3C6C6C3C6C6C3C6848284848284C6C3C6FFFFFF000000848284
          8482848482848482848482848482848482848482848482840000848284848284
          848284848284848284848284848284848284000000000000FFFFFFFFFFFFC6C3
          C6FFFF00C6C3C6FFFF00C6C3C6FFFF00FFFFFFFFFFFFC6C3C6C6C3C6FFFFFF00
          0000848284848284848284848284848284848284848284848284848284848284
          0000848284848284848284848284848284848284848284848284848284848284
          000000000000FFFFFFFFFFFFFFFF00C6C3C6FFFF00C6C3C6FFFF00C6C3C6FFFF
          00FFFFFFFFFFFF00000084828484828484828484828484828484828484828484
          8284848284848284000084828484828484828484828484828484828484828484
          8284848284848284848284848284000000000000FFFFFFFFFFFFC6C3C6FFFF00
          C6C3C6FFFFFFFFFFFFFFFFFF0000008482848482848482848482848482848482
          8484828484828484828484828484828400008482848482848482848482848482
          8484828484828484828484828484828484828484828484828484828400000000
          0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000848284848284848284848284
          8482848482848482848482848482848482848482848482840000848284848284
          8482848482848482848482848482848482848482848482848482848482848482
          8484828484828484828400000000000000000000000000000084828484828484
          8284848284848284848284848284848284848284848284848284848284848284
          0000848284848284848284848284848284848284848284848284848284848284
          8482848482848482848482848482848482848482848482848482848482848482
          8484828484828484828484828484828484828484828484828484828484828484
          82848482848482840000CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CE
          D3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6
          CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3
          D6CED3D6CED3D6CED3D6CED3D6CED3D60000}
        Margin = 4
      end
    end
    object relative_to_sim_tabsheet: TTabSheet
      Caption = 'Relative to simulation period'
      ImageIndex = 2
      object Label2: TLabel
        Left = 56
        Top = 20
        Width = 24
        Height = 13
        Caption = 'Days'
      end
      object from_sim_event_days_edit: TAutoInt16Edit
        Left = 8
        Top = 16
        Width = 38
        Height = 24
        Alignment = taRightJustify
        Lines.Strings = (
          '0')
        TabOrder = 0
        WantReturns = False
      end
      object sim_event_radiogroup: TAutoRadioGroup
        Left = 96
        Top = 0
        Width = 169
        Height = 132
        Anchors = [akLeft, akTop, akBottom]
        Caption = 'Simulation event'
        ItemIndex = 0
        Items.Strings = (
          'after start of simulation'
          'before end of simulation')
        TabOrder = 1
      end
    end
    object relative_to_sow_tabsheet: TTabSheet
      Caption = 'Relative to sowing date'
      object Label3: TLabel
        Left = 0
        Top = 219
        Width = 520
        Height = 37
        Anchors = [akLeft, akRight, akBottom]
        AutoSize = False
        Caption = 
          'Note that the actual day of month and day of week will depend on' +
          ' the year the event occurs and leap year condition.'
        WordWrap = True
      end
      object Label4: TLabel
        Left = 168
        Top = 96
        Width = 40
        Height = 13
        Caption = 'Nth year'
      end
      object relative_year_radiogroup: TAutoRadioGroup
        Left = 0
        Top = 56
        Width = 153
        Height = 85
        Caption = 'Relative year'
        Items.Strings = (
          'Sowing year'
          'First year after sowing'
          'Nth year after sowing'
          'Nth year before sowing')
        TabOrder = 0
        OnClick = relative_year_radiogroup_onclick
      end
      object relative_year_intedit: TAutoInt16Edit
        Left = 173
        Top = 115
        Width = 33
        Height = 24
        Alignment = taRightJustify
        Lines.Strings = (
          '0')
        TabOrder = 1
        WantReturns = False
        OnChange = relative_year_intedit_onchange
        OnExit = relative_year_intedit_onchange
      end
      object relative_to_sowing_datebutton: TAutoDateButton
        Left = 8
        Top = 8
        Width = 507
        Height = 41
        Hint = 'Click here to select relative date'
        Anchors = [akLeft, akTop, akRight]
        Caption = 'Relative to sowing date'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 2
        Glyph.Data = {
          6E0E0000424D6E0E000000000000360000002800000022000000230000000100
          180000000000380E000000000000000000000000000000000000848284848284
          8482848482848482848482848482848482848482848482848482848482848482
          8484828484828484828484828484828484828484828484828484828484828484
          8284848284848284848284848284848284848284848284848284848284848284
          0000848284848284848284848284848284848284848284848284848284848284
          8482848482840000000000000000008482848482848482848482848482848482
          8484828484828484828484828484828484828484828484828484828484828484
          8284848284848284000084828484828484828484828484828484828484828484
          8284848284848284848284000000848284C6C3C6000000000000000000848284
          8482848482848482848482848482848482848482848482848482848482848482
          8484828484828484828484828484828400008482848482848482848482848482
          84848284848284848284848284848284848284000000C6C3C6FFFFFFFFFFFFC6
          C3C6000000000000000000848284848284848284848284848284848284848284
          8482848482848482848482848482848482848482848482840000848284848284
          848284848284848284848284848284848284848284848284000000848284C6C3
          C6FFFFFFC6C3C6FFFFFFFFFFFFC6C3C600000000000000000084828484828484
          8284848284848284848284848284848284848284848284848284848284848284
          0000848284848284848284848284848284848284848284848284848284848284
          000000C6C3C6FFFFFFFFFFFFC6C3C6FFFFFFC6C3C6FFFFFFFFFFFFC6C3C60000
          0000000000000084828484828484828484828484828484828484828484828484
          8284848284848284000084828484828484828484828484828484828484828484
          8284848284000000848284C6C3C6FFFFFFC6C3C6FFFFFFFFFFFFC6C3C6FFFFFF
          C6C3C6FFFFFFFFFFFFC6C3C60000000000000000008482848482848482848482
          8484828484828484828484828484828400008482848482848482848482848482
          84848284848284848284848284000000C6C3C6FFFFFFFFFFFFC6C3C6FFFFFFC6
          C3C6FFFFFFFFFFFFC6C3C6FFFFFFC6C3C6FFFFFFFFFFFFC6C3C6000000000000
          0000008482848482848482848482848482848482848482840000848284848284
          848284848284848284848284848284848284000000848284C6C3C6FFFFFFC6C3
          C6FFFFFFFFFFFFC6C3C6FFFFFFC6C3C6FFFFFFFFFFFFC6C3C6FFFFFFC6C3C6FF
          FFFFFFFFFFC6C3C6000000000000000000848284848284848284848284848284
          0000848284848284848284848284848284848284848284848284000000C6C3C6
          FFFFFFFFFFFFC6C3C6FFFFFFC6C3C6FFFFFFFFFFFFC6C3C6FFFFFFC6C3C6FFFF
          FFFFFFFFC6C3C6FFFFFFC6C3C6FFFFFFFFFFFFC6C3C600000000000000000084
          8284848284848284000084828484828484828484828484828484828484828400
          0000848284C6C3C6FFFFFFC6C3C6FFFFFFFFFFFFC6C3C6FFFFFFC6C3C6FFFFFF
          FFFFFFC6C3C6FFFFFFC6C3C6FFFFFFFFFFFFC6C3C6FFFFFFC6C3C6FFFFFFFFFF
          FFC6C3C600000000000084828484828400008482848482848482848482848482
          84848284848284000000C6C3C6FFFFFFFFFFFFC6C3C6FFFFFFC6C3C6FFFFFFFF
          FFFFC6C3C6FFFFFFC6C3C6FFFFFF000084000084000084C6C3C6FFFFFFFFFFFF
          C6C3C6FFFFFFC6C3C6FFFFFFC6C3C60000008482848482840000848284848284
          848284848284848284848284000000848284C6C3C6FFFFFFC6C3C6FFFFFFFFFF
          FFC6C3C6FFFFFFC6C3C6FFFFFFFFFFFFC6C3C6000084FFFFFFFFFFFFFFFFFF00
          0084C6C3C6C6C3C6FFFFFFFFFFFFC6C3C6FFFFFF000000848284848284848284
          0000848284848284848284848284848284848284000000C6C3C6FFFFFF840000
          840000C6C3C6C6C3C6FFFFFFFFFFFFC6C3C6FFFFFFC6C3C6FFFFFF000084FFFF
          FFFFFFFFFFFFFFFFFFFF000084C6C3C6FFFFFFC6C3C6FFFFFF00000084828484
          82848482848482840000848284848284848284848284848284000000848284C6
          C3C6FFFFFF840000840000840000840000C6C3C6C6C3C6FFFFFFFFFFFFC6C3C6
          FFFFFFC6C3C6000084FFFFFFFFFFFFFFFFFF000084FFFFFFFFFFFFC6C3C6FFFF
          FF00000084828484828484828484828400008482848482848482848482848482
          84000000848284848284848284FFFFFFFFFFFF840000840000840000840000C6
          C3C6C6C3C6FFFFFFFFFFFFC6C3C6FFFFFF000084000084000084C6C3C6FFFFFF
          C6C3C6FFFFFF0000008482848482848482848482848482840000848284848284
          848284848284848284848284000000C6C3C6C6C3C6848284848284FFFFFFFFFF
          FF840000840000848284848284C6C3C6C6C3C6FFFFFFFFFFFFC6C3C6FFFFFFC6
          C3C6FFFFFFFFFFFFC6C3C6FFFFFF000000848284848284848284848284848284
          0000848284848284848284848284848284848284000000FFFFFF008200C6C3C6
          C6C3C6848284848284FFFFFFFFFFFF848284848284848284848284C6C3C6C6C3
          C6FFFFFFFFFFFFC6C3C6FFFFFFC6C3C6FFFFFF00000084828484828484828484
          82848482848482840000848284848284848284848284848284000000C6C3C6FF
          FFFF008200008200008200C6C3C6C6C3C6848284848284FFFFFFFFFFFF848284
          848284848284848284C6C3C6C6C3C6FFFFFFFFFFFFC6C3C6FFFFFF0000008482
          8484828484828484828484828484828400008482848482848482848482848482
          84000000FFFFFFC6C3C6008200008200008200008200008200C6C3C6C6C3C684
          8284848284FFFFFFFFFFFF848284848284848284848284C6C3C6C6C3C6FFFFFF
          0000008482848482848482848482848482848482848482840000848284848284
          848284848284000000C6C3C6FFFFFF8482840082000082000082000082000082
          00008200008200C6C3C6C6C3C6848284848284FFFFFFFFFFFF84828484828484
          8284C6C3C6FFFFFF000000848284848284848284848284848284848284848284
          0000848284848284848284848284000000C6C3C6C6C3C6848284848200C6C3C6
          008200008200008200008200008200008200008200C6C3C6C6C3C68482848482
          84FFFFFFFFFFFF848284FFFFFF00000084828484828484828484828484828484
          82848482848482840000848284848284848284000000C6C3C6FFFFFFC6C3C6FF
          FF00848284848200C6C3C6008200008200008200008200008200008200008200
          008200C6C3C6C6C3C6848284848284FFFFFFFFFFFF0000008482848482848482
          848482848482848482848482848482840000848284848284000000C6C3C6FFFF
          FFC6C3C6FFFF00C6C3C6FFFFFFFFFFFFC6C3C600820000820000820000820000
          8200008200008200008200008200008200C6C3C6C6C3C6848284000000848284
          8482848482848482848482848482848482848482848482840000848284000000
          FFFFFFFFFFFFC6C3C6FFFF00C6C3C6FFFF00C6C3C6FFFF00C6C3C6FFFFFFFFFF
          FF008200008200008200008200008200008200008200008200008200008200C6
          C3C6000000848284848284848284848284848284848284848284848284848284
          0000848284848284000000000000FFFFFFFFFFFFFFFF00C6C3C6FFFF00C6C3C6
          FFFF00C6C3C6FFFFFFFFFFFFFFFFFF0082000082000082000082000082000082
          00008200008200FFFFFF00000084828484828484828484828484828484828484
          82848482848482840000848284848284848284848284000000000000FFFFFFFF
          FFFFC6C3C6FFFF00C6C3C6FFFF00FFFFFFFFFFFFFFFFFFFFFFFFC6C3C6C6C3C6
          C6C3C6008200008200008200008200FFFFFF0000008482848482848482848482
          8484828484828484828484828484828400008482848482848482848482848482
          84848284000000000000FFFFFFFFFFFFFFFF00C6C3C6FFFF00C6C3C6FFFF00C6
          C3C6FFFF00C6C3C6C6C3C6C6C3C6848284848284C6C3C6FFFFFF000000848284
          8482848482848482848482848482848482848482848482840000848284848284
          848284848284848284848284848284848284000000000000FFFFFFFFFFFFC6C3
          C6FFFF00C6C3C6FFFF00C6C3C6FFFF00FFFFFFFFFFFFC6C3C6C6C3C6FFFFFF00
          0000848284848284848284848284848284848284848284848284848284848284
          0000848284848284848284848284848284848284848284848284848284848284
          000000000000FFFFFFFFFFFFFFFF00C6C3C6FFFF00C6C3C6FFFF00C6C3C6FFFF
          00FFFFFFFFFFFF00000084828484828484828484828484828484828484828484
          8284848284848284000084828484828484828484828484828484828484828484
          8284848284848284848284848284000000000000FFFFFFFFFFFFC6C3C6FFFF00
          C6C3C6FFFFFFFFFFFFFFFFFF0000008482848482848482848482848482848482
          8484828484828484828484828484828400008482848482848482848482848482
          8484828484828484828484828484828484828484828484828484828400000000
          0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000848284848284848284848284
          8482848482848482848482848482848482848482848482840000848284848284
          8482848482848482848482848482848482848482848482848482848482848482
          8484828484828484828400000000000000000000000000000084828484828484
          8284848284848284848284848284848284848284848284848284848284848284
          0000848284848284848284848284848284848284848284848284848284848284
          8482848482848482848482848482848482848482848482848482848482848482
          8484828484828484828484828484828484828484828484828484828484828484
          82848482848482840000CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CE
          D3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6
          CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3
          D6CED3D6CED3D6CED3D6CED3D6CED3D60000}
        Margin = 4
      end
    end
    object before_planting_tabsheet: TTabSheet
      Caption = 'Before planting'
      ImageIndex = 4
      object before_planting_note: TLabel
        Left = 16
        Top = 96
        Width = 475
        Height = 33
        Anchors = [akLeft, akTop, akRight]
        AutoSize = False
        Caption = 
          'This synchronization mode can be use to specify events or period' +
          's that occur before sowing of crops or planting of fruit trees.'
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
      end
      object Label5: TLabel
        Left = 56
        Top = 20
        Width = 24
        Height = 13
        Caption = 'Days'
      end
      object before_planting_days_intedit: TAutoInt16Edit
        Left = 8
        Top = 16
        Width = 38
        Height = 24
        Alignment = taRightJustify
        Lines.Strings = (
          '0')
        TabOrder = 0
        WantReturns = False
      end
    end
    object normal_phenologic_tabsheet: TTabSheet
      Caption = 'Crop phenology'
      ImageIndex = 1
      object phen_sync_days_label: TLabel
        Left = 56
        Top = 4
        Width = 24
        Height = 13
        Caption = 'Days'
      end
      object Label8: TLabel
        Left = 264
        Top = 184
        Width = 188
        Height = 33
        Anchors = [akLeft, akTop, akRight]
        AutoSize = False
        Caption = 'and repeat event each growing season.'
        Visible = False
        WordWrap = True
      end
      object Label11: TLabel
        Left = 200
        Top = 144
        Width = 305
        Height = 81
        Anchors = [akLeft, akTop, akRight]
        AutoSize = False
        Caption = 
          'For perennials, the planting, sowing and emergence will not be r' +
          'epeated so these synchronizations should not be used to repeat e' +
          'vents. This options is most important when clipping events may r' +
          'eset phenology.'
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
      end
      object Label14: TLabel
        Left = 200
        Top = 68
        Width = 305
        Height = 69
        Anchors = [akLeft, akTop, akRight]
        AutoSize = False
        Caption = 
          'Start of successive seasons is intended for perennials, indicati' +
          'ng events that occur only in seasons after the first year, or fo' +
          'r annuals that have a dormancy period (I.e. winter wheat). Other' +
          'wise use '#39'After start of Emergence'#39'.'
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
      end
      object crop_phen_sync_days_intedit: TAutoInt16Edit
        Left = 8
        Top = 0
        Width = 38
        Height = 24
        Alignment = taRightJustify
        Lines.Strings = (
          '0')
        TabOrder = 0
        WantReturns = False
        OnChange = crop_phen_sync_days_intedit_onchange
        OnExit = crop_phen_sync_days_intedit_onchange
      end
      object crop_phen_sync_radiogroup: TAutoRadioGroup
        Left = 8
        Top = 24
        Width = 185
        Height = 230
        Anchors = [akLeft, akTop, akBottom]
        Caption = 'After start of'
        Items.Strings = (
          'nothing (<- don'#39't use this)'
          'Sowing'
          'Germination'
          'Emergence'
          'Start of successive seasons'
          'Active growth'
          'End canopy growth'
          'Flowering'
          'Yield formation (Grain filling bulking)'
          'undefined (stage reserved for future use)'
          'undefined (stage reserved for future use)'
          'Maturity'
          'Harvestable (<- don'#39't use this)'
          'Harvest'
          'Dormancy')
        TabOrder = 1
      end
      object normal_crop_phen_reschedule_checkbox: TAutoCheckBox
        Left = 240
        Top = 184
        Width = 225
        Height = 17
        Caption = 'Reschedule (obsolete)'
        TabOrder = 2
        Visible = False
      end
      object normal_crop_phen_reschedule_radio: TAutoRadioGroup
        Left = 192
        Top = 0
        Width = 329
        Height = 65
        Hint = 
          'Reschedule in the case where there may be events (I.e. clipping)' +
          ' that reset phenology. Generally applied only to perennials.'
        Anchors = [akLeft, akTop, akRight]
        Caption = 'Option for rescheduling this event in successive seasons.'
        Items.Strings = (
          
            'Don'#39't reschedule (only do this once in the life time of this cro' +
            'p)'
          'No more than once each season'
          
            'Whenever this phenogic stage is achieved (perhaps multiple event' +
            's each season)')
        ParentShowHint = False
        ShowHint = True
        TabOrder = 3
      end
    end
    object fruit_tree_phenologic_tabsheet: TTabSheet
      Caption = 'Fruit tree phenology'
      ImageIndex = 5
      object Label6: TLabel
        Left = 56
        Top = 4
        Width = 24
        Height = 13
        Caption = 'Days'
      end
      object Label9: TLabel
        Left = 328
        Top = 200
        Width = 188
        Height = 33
        Anchors = [akLeft, akTop, akRight]
        AutoSize = False
        Caption = 'and repeat event each growing season.'
        Visible = False
        WordWrap = True
      end
      object Label12: TLabel
        Left = 328
        Top = 104
        Width = 180
        Height = 146
        Anchors = [akLeft, akTop, akRight, akBottom]
        AutoSize = False
        Caption = 
          'For perennials, the planting, sowing and emergence will not be r' +
          'epeated so these synchronizations should not be used to repeat e' +
          'vents. This options is most important when clipping events may r' +
          'eset phenology.'
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
      end
      object Label13: TLabel
        Left = 200
        Top = 104
        Width = 121
        Height = 146
        Anchors = [akLeft, akTop, akBottom]
        AutoSize = False
        Caption = 
          'For fruit trees, most operations are rescheduled. Use the option' +
          ' "No more than once each season", or "Whenever .. achieved"'
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
      end
      object fruit_phen_sync_days_intedit: TAutoInt16Edit
        Left = 8
        Top = 0
        Width = 38
        Height = 24
        Alignment = taRightJustify
        Lines.Strings = (
          '0')
        TabOrder = 0
        WantReturns = False
        OnChange = crop_phen_sync_days_intedit_onchange
        OnExit = crop_phen_sync_days_intedit_onchange
      end
      object fruit_phen_sync_radiogroup: TAutoRadioGroup
        Left = 8
        Top = 24
        Width = 185
        Height = 226
        Anchors = [akLeft, akTop, akBottom]
        Caption = 'After start of'
        Items.Strings = (
          'nothing (<- don'#39't use this)'
          'Planting (root stock)'
          'undefined (reserved for future use)'
          'undefined (reserved for future use)'
          'Bud break'
          'Active growth'
          'End canopy growth'
          'Flowering'
          'Fruit development'
          'Veraison (grapes)'
          'Rapid fruit development'
          'Maturity'
          'Harvestable'
          'Harvest'
          'Dormancy'
          'Terminated')
        TabOrder = 1
      end
      object fruit_tree_phen_reschedule_checkbox: TAutoCheckBox
        Left = 328
        Top = 184
        Width = 225
        Height = 17
        Caption = 'Reschedule  (obsolete)'
        TabOrder = 2
        Visible = False
      end
      object fruit_tree_phen_reschedule_radio: TAutoRadioGroup
        Left = 200
        Top = 0
        Width = 321
        Height = 97
        Hint = 
          'Reschedule in the case where there may be events (I.e. clipping)' +
          ' that reset phenology. Generally applied only to perennials.'
        Anchors = [akLeft, akTop, akRight]
        Caption = 'Option for rescheduling this event in successive seasons.'
        Items.Strings = (
          
            'Don'#39't reschedule (only do this once in the life time of this cro' +
            'p)'
          'No more than once each season'
          
            'Whenever this phenogic stage is achieved (perhaps multiple event' +
            's each season)')
        ParentShowHint = False
        ShowHint = True
        TabOrder = 3
      end
    end
    object thermal_time_tabsheet: TTabSheet
      Caption = 'Thermal time'
      ImageIndex = 6
      object Label1: TLabel
        Left = 16
        Top = 144
        Width = 475
        Height = 33
        Anchors = [akLeft, akTop, akRight]
        AutoSize = False
        Caption = 
          'This thermal time refers to the thermal time accumulation starti' +
          'ng at crop sowing, end of dorumancy (perennials) , or  fruit tre' +
          'e bud break.'
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
      end
      object Label10: TLabel
        Left = 320
        Top = 24
        Width = 188
        Height = 33
        AutoSize = False
        Caption = 'and repeat event each growing season.'
        Visible = False
        WordWrap = True
      end
      object thermal_time_intedit: TAutoInt16EditBar
        Left = 8
        Top = 12
        Width = 273
        Height = 22
        AutoScroll = False
        TabOrder = 0
        TabStop = True
        Description_label = 'Thermal time'
        Units_label = 'degree days'
      end
      object thermal_time_reschedule_checkbox: TAutoCheckBox
        Left = 296
        Top = 8
        Width = 225
        Height = 17
        Caption = 'Reschedule'
        TabOrder = 1
        Visible = False
      end
      object thermal_time_reschedule_radio: TAutoRadioGroup
        Left = 8
        Top = 40
        Width = 513
        Height = 97
        Hint = 
          'Reschedule in the case where there may be events (I.e. clipping)' +
          ' that reset phenology. Generally applied only to perennials.'
        Anchors = [akLeft, akTop, akRight]
        Caption = 'Option for rescheduling this event in successive seasons.'
        Items.Strings = (
          
            'Don'#39't reschedule (only do this once in the life time of this cro' +
            'p)'
          'No more than once each season'
          
            'Whenever this phenogic stage is achieved (perhaps multiple event' +
            's each season)')
        ParentShowHint = False
        ShowHint = True
        TabOrder = 2
      end
    end
  end
end
