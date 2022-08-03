object auto_clipping_form: Tauto_clipping_form
  Left = 991
  Top = 258
  Align = alClient
  Caption = 'auto_clipping_form'
  ClientHeight = 326
  ClientWidth = 473
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
    Width = 473
    Height = 326
    ActivePage = condition_tabsheet
    Align = alClient
    TabOrder = 0
    object condition_tabsheet: TTabSheet
      Caption = 'Conditions that force clipping/harvest'
      DesignSize = (
        465
        298)
      object Label1: TLabel
        Left = 8
        Top = 0
        Width = 449
        Height = 41
        AutoSize = False
        Caption = 
          'Any of the following enabled conditions may trigger the clipping' +
          '/grazing/harvest event (these conditions are '#39'or'#39' not '#39'and'#39' I.e.' +
          '  consider growth rate or consider LAI or consider Biomass or co' +
          'nsider flowering.).'
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
      end
      object adjust_rate_clip_edit: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 24
        Top = 63
        Width = 433
        Height = 22
        Hint = 
          'This growth rate adjustment accelerates (above 1) or delays clip' +
          'ping (below 1) and it is used as a multiplier to what is conside' +
          'red a low green area index growth rate, which is a fixed value e' +
          'mbedded in the code (0.05 GAI/day). '
        Alignment = taLeftJustify
        Anchors = [akLeft, akRight]
        BevelOuter = bvNone
        Caption = 'Relative growth rate adjustement'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
      end
      object biomass_forces_clip_edit: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 24
        Top = 159
        Width = 433
        Height = 22
        Alignment = taLeftJustify
        Anchors = [akLeft, akRight]
        BevelOuter = bvNone
        Caption = 'Maximum biomass that forces clipping'
        TabOrder = 5
      end
      object LAI_forces_clip_edit: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 24
        Top = 111
        Width = 433
        Height = 22
        Alignment = taLeftJustify
        Anchors = [akLeft, akRight]
        BevelOuter = bvNone
        Caption = 'Maximum LAI that forces clipping'
        TabOrder = 3
      end
      object flowering_forces_clip_edit: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 24
        Top = 208
        Width = 433
        Height = 22
        Hint = 
          'This is usually used with alfalfa to clip as the plants flower o' +
          'r reflower'
        Alignment = taLeftJustify
        Anchors = [akLeft, akRight]
        BevelOuter = bvNone
        Caption = 'Number of days after flowering forces clipping'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 7
      end
      object adjust_rate_clip_checkbox: TRNAutoCheckBox
        Left = 8
        Top = 44
        Width = 449
        Height = 17
        Hint = 'This growth rate adjustment accelerates or delays clipping '
        Anchors = [akLeft, akRight]
        Caption = 'Consider relative growth rate adjustement'
        TabOrder = 0
        OnClick = show_hide_controls
      end
      object LAI_forces_clip_checkbox: TRNAutoCheckBox
        Left = 8
        Top = 92
        Width = 449
        Height = 17
        Hint = 'Clip when LAI is reached'
        Anchors = [akLeft, akRight]
        Caption = 'Consider LAI status'
        TabOrder = 2
        OnClick = show_hide_controls
      end
      object biomass_forces_clip_checkbox: TRNAutoCheckBox
        Left = 8
        Top = 140
        Width = 449
        Height = 17
        Hint = 'Clip when biomass is reached'
        Anchors = [akLeft, akRight]
        Caption = 'Consider Biomass status'
        Checked = True
        State = cbChecked
        TabOrder = 4
        OnClick = show_hide_controls
      end
      object flowering_forces_clip_checkbox: TRNAutoCheckBox
        Left = 8
        Top = 188
        Width = 449
        Height = 17
        Hint = 'Clip based on flowering'
        Anchors = [akLeft, akRight]
        Caption = 'Consider flowering status'
        TabOrder = 6
        OnClick = show_hide_controls
      end
    end
    object operation_tabsheet: TTabSheet
      Caption = 'Operation constraints and biomatter fate'
      ImageIndex = 1
    end
  end
end
