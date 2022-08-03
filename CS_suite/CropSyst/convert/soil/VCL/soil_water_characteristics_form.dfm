object form_soil_water_characteristics: Tform_soil_water_characteristics
  Left = 765
  Top = 110
  Width = 807
  Height = 528
  VertScrollBar.Visible = False
  Anchors = [akLeft, akTop, akRight]
  Caption = 'Soil water characteristics'
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
  object GroupBox3: TGroupBox
    Left = 328
    Top = 8
    Width = 464
    Height = 305
    Anchors = [akLeft, akTop, akRight]
    Caption = 'Estimated hydraulic properties'
    TabOrder = 2
    object grid_hydraulic_properties: TAdvStringGrid
      Left = 2
      Top = 15
      Width = 460
      Height = 263
      Cursor = crDefault
      Align = alClient
      ColCount = 4
      DefaultColWidth = 70
      DefaultRowHeight = 21
      RowCount = 9
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goDrawFocusSelected, goEditing]
      ParentFont = False
      ScrollBars = ssBoth
      TabOrder = 0
      ActiveCellFont.Charset = DEFAULT_CHARSET
      ActiveCellFont.Color = clWindowText
      ActiveCellFont.Height = -11
      ActiveCellFont.Name = 'Tahoma'
      ActiveCellFont.Style = [fsBold]
      ColumnHeaders.Strings = (
        'Model:'
        'Saxton & al. 1986'
        'Saxton & Rawls 2006 unadjusted'
        'Saxton & Rawls 2006 effective'
        '')
      Filter = <>
      FixedColWidth = 180
      FixedRowHeight = 50
      FixedFont.Charset = DEFAULT_CHARSET
      FixedFont.Color = clWindowText
      FixedFont.Height = -11
      FixedFont.Name = 'Tahoma'
      FixedFont.Style = [fsBold]
      FloatFormat = '%.2f'
      PrintSettings.DateFormat = 'dd/mm/yyyy'
      PrintSettings.Font.Charset = DEFAULT_CHARSET
      PrintSettings.Font.Color = clWindowText
      PrintSettings.Font.Height = -11
      PrintSettings.Font.Name = 'MS Sans Serif'
      PrintSettings.Font.Style = []
      PrintSettings.FixedFont.Charset = DEFAULT_CHARSET
      PrintSettings.FixedFont.Color = clWindowText
      PrintSettings.FixedFont.Height = -11
      PrintSettings.FixedFont.Name = 'MS Sans Serif'
      PrintSettings.FixedFont.Style = []
      PrintSettings.HeaderFont.Charset = DEFAULT_CHARSET
      PrintSettings.HeaderFont.Color = clWindowText
      PrintSettings.HeaderFont.Height = -11
      PrintSettings.HeaderFont.Name = 'MS Sans Serif'
      PrintSettings.HeaderFont.Style = []
      PrintSettings.FooterFont.Charset = DEFAULT_CHARSET
      PrintSettings.FooterFont.Color = clWindowText
      PrintSettings.FooterFont.Height = -11
      PrintSettings.FooterFont.Name = 'MS Sans Serif'
      PrintSettings.FooterFont.Style = []
      PrintSettings.PageNumSep = '/'
      RowHeaders.Strings = (
        'Model:'
        'Matric bulk density (g/cm³)'
        'Wilting point (m³/m³)'
        'Field capacity (m³/m³)'
        'Sat. hydr. cond. (m/day)'
        'Air entry pot. (J/kg)'
        'Campbell B'
        'Saturation (m³/m³)'
        'Available water (cm/cm)')
      ScrollWidth = 16
      SearchFooter.FindNextCaption = 'Find next'
      SearchFooter.FindPrevCaption = 'Find previous'
      SearchFooter.Font.Charset = DEFAULT_CHARSET
      SearchFooter.Font.Color = clWindowText
      SearchFooter.Font.Height = -11
      SearchFooter.Font.Name = 'MS Sans Serif'
      SearchFooter.Font.Style = []
      SearchFooter.HighLightCaption = 'Highlight'
      SearchFooter.HintClose = 'Close'
      SearchFooter.HintFindNext = 'Find next occurence'
      SearchFooter.HintFindPrev = 'Find previous occurence'
      SearchFooter.HintHighlight = 'Highlight occurences'
      SearchFooter.MatchCaseCaption = 'Match case'
      ColWidths = (
        180
        70
        70
        70)
      RowHeights = (
        50
        21
        21
        21
        21
        21
        21
        21
        21)
    end
    object panel_hydraulic_properties_buttons: TPanel
      Left = 2
      Top = 278
      Width = 460
      Height = 25
      Hint = 
        'Entering a user specified (I.e. measured value) will automatical' +
        'ly lock the value. '
      Align = alBottom
      BevelOuter = bvNone
      ParentShowHint = False
      ShowHint = True
      TabOrder = 1
      object label_resets: TLabel
        Left = 271
        Top = 0
        Width = 189
        Height = 25
        Align = alRight
        AutoSize = False
        Caption = 
          'Selecting a new texture (sand-clay) unlocks and recalclates all ' +
          'entries.'
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
      end
      object button_unlock_user_value: TBitBtn
        Left = 8
        Top = 0
        Width = 120
        Height = 25
        Caption = 'Unlock cell value'
        TabOrder = 0
        OnClick = button_unlock_user_valueClick
        Glyph.Data = {
          76010000424D7601000000000000760000002800000020000000100000000100
          04000000000000010000120B0000120B00001000000000000000000000000000
          800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333000003
          333333333F777773FF333333008888800333333377333F3773F3333077870787
          7033333733337F33373F3308888707888803337F33337F33337F330777880887
          7703337F33337FF3337F3308888000888803337F333777F3337F330777700077
          7703337F33377733337FB3088888888888033373FFFFFFFFFF733B3000000000
          0033333777777777773333BBBB3333080333333333F3337F7F33BBBB707BB308
          03333333373F337F7F3333BB08033308033333337F7F337F7F333B3B08033308
          033333337F73FF737F33B33B778000877333333373F777337333333B30888880
          33333333373FFFF73333333B3300000333333333337777733333}
        NumGlyphs = 2
      end
      object button_lock_user_value: TBitBtn
        Left = 134
        Top = 0
        Width = 120
        Height = 25
        Caption = 'Lock cell value'
        TabOrder = 1
        OnClick = button_lock_user_valueClick
        Glyph.Data = {
          76010000424D7601000000000000760000002800000020000000100000000100
          04000000000000010000120B0000120B00001000000000000000000000000000
          800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333000003
          333333333F777773FF333333008888800333333377333F3773F3333077870787
          7033333733337F33373F3308888707888803337F33337F33337F330777880887
          7703337F33337FF3337F3308888000888803337F333777F3337F330777700077
          7703337F33377733337F33088888888888033373FFFFFFFFFF73333000000000
          00333337777777777733333308033308033333337F7F337F7F33333308033308
          033333337F7F337F7F33333308033308033333337F73FF737F33333377800087
          7333333373F77733733333333088888033333333373FFFF73333333333000003
          3333333333777773333333333333333333333333333333333333}
        NumGlyphs = 2
      end
    end
  end
  object groupbox_texture: TGroupBox
    Left = 0
    Top = 8
    Width = 321
    Height = 105
    Caption = 'Texture'
    TabOrder = 3
    object label_fine_soil_basis: TLabel
      Left = 2
      Top = 15
      Width = 317
      Height = 13
      Align = alTop
      AutoSize = False
      Caption = 'Enter sand and clay as fine earth basis (excluding gravel).'
      Color = clInfoBk
      ParentColor = False
      WordWrap = True
    end
    object edit_sand: TAutoFloat32EditBar
      Left = 2
      Top = 28
      Width = 317
      Height = 21
      Hint = 'Sand is fine soil basis (excluding gravel)'
      Align = alTop
      AutoScroll = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      OnExit = edit_parameter_adjusted
      Description_label = 'Sand'
      Units_label = 'units'
    end
    object edit_clay: TAutoFloat32EditBar
      Left = 2
      Top = 49
      Width = 317
      Height = 21
      Hint = 'Clay is fine soil basis (excluding gravel)'
      Align = alTop
      AutoScroll = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 1
      OnExit = edit_parameter_adjusted
      Description_label = 'Clay'
      Units_label = '%'
    end
    object button_select_texture: TBitBtn
      Left = 8
      Top = 74
      Width = 105
      Height = 25
      Caption = 'Select texture'
      TabOrder = 2
      OnClick = button_select_textureClick
      Glyph.Data = {
        36050000424D3605000000000000360400002800000010000000100000000100
        08000000000000010000110B0000150B00000001000000000000000000000000
        8000008000000080800080000000800080008080000080808000840404000404
        84000484840004840400840484008484840084840400C4C4C400FC0404000404
        FC0004FC0400FC04FC00FCFC0400FCFCFC000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF000F0F0F0F0F0F
        0F0F0F0F0F0F0F0F0F0F0F090911110A0A0808080F0F0F0F0F070F0111111103
        030404100F0F0F0F07070F1111111103030810100F0F0F0707070F1111111105
        051010100F0F070707070F1111111305051010100F07070707070F111113130C
        051010100707070707070F1113131305051010070707070707070F0613131212
        0B0207070707070707070F06060612120B0707070707070707070F0606061212
        070707070707070707070F1406061207070707070707070707070F14140E0707
        070707070707070707070F0F14070707070707070707070707070F0F07070707
        070707070707070707070F070707070707070707070707070707}
    end
    object combobox_texture: TComboBox
      Left = 120
      Top = 76
      Width = 193
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      ItemHeight = 13
      TabOrder = 3
      Text = 'loam'
      OnChange = combobox_textureChange
    end
  end
  object Panel1: TPanel
    Left = 328
    Top = 352
    Width = 464
    Height = 113
    Anchors = [akLeft, akTop, akRight]
    TabOrder = 4
    object Label9: TLabel
      Left = 80
      Top = 88
      Width = 304
      Height = 13
      Alignment = taCenter
      Anchors = [akLeft, akTop, akRight]
      AutoSize = False
      Caption = '30'
    end
    object Label2: TLabel
      Left = 1
      Top = 99
      Width = 462
      Height = 13
      Align = alBottom
      Alignment = taCenter
      Caption = 'Soil moisture (m³/m³)'
    end
    object Label3: TLabel
      Left = 1
      Top = 1
      Width = 41
      Height = 26
      Caption = 'Potential (kPa)'
      WordWrap = True
    end
    object Label4: TLabel
      Left = 9
      Top = 33
      Width = 29
      Height = 13
      Caption = 'Matric'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clLime
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      WordWrap = True
    end
    object Label5: TLabel
      Left = 9
      Top = 48
      Width = 38
      Height = 26
      Caption = 'Matric + Osmotic'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      WordWrap = True
    end
    object label_hydr_cond_axis: TLabel
      Left = 391
      Top = 8
      Width = 33
      Height = 89
      Anchors = [akTop, akRight]
      AutoSize = False
      Caption = '100  10      1     0.0 0.001 0.0001'
      WordWrap = True
    end
    object label_potential_axis_1500: TLabel
      Left = 48
      Top = 8
      Width = 27
      Height = 89
      Alignment = taRightJustify
      AutoSize = False
      Caption = '1500  1200  900   600    300       0'
      WordWrap = True
    end
    object image_graph: TImage
      Left = 80
      Top = 16
      Width = 304
      Height = 65
      Anchors = [akLeft, akTop, akRight]
    end
    object label_potential_axis_50: TLabel
      Left = 52
      Top = 8
      Width = 17
      Height = 81
      Alignment = taRightJustify
      AutoSize = False
      Caption = '50 40 30 20 10 0'
      WordWrap = True
    end
    object Label6: TLabel
      Left = 422
      Top = 24
      Width = 41
      Height = 41
      Anchors = [akTop, akRight]
      AutoSize = False
      Caption = 'Hydr. cond. (mm/hr)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      WordWrap = True
    end
    object Label7: TLabel
      Left = 77
      Top = 88
      Width = 6
      Height = 13
      Caption = '0'
    end
    object Label8: TLabel
      Left = 377
      Top = 88
      Width = 12
      Height = 13
      Anchors = [akTop, akRight]
      Caption = '60'
    end
  end
  object groupbox_effects: TGroupBox
    Left = 0
    Top = 120
    Width = 321
    Height = 377
    Anchors = [akLeft, akTop, akRight]
    Caption = 'Effects'
    TabOrder = 5
    object scrollbox_effects: TScrollBox
      Left = 2
      Top = 15
      Width = 317
      Height = 360
      Align = alClient
      BorderStyle = bsNone
      TabOrder = 0
      object edit_organic_matter: TAutoFloat32EditBar
        Left = 0
        Top = 0
        Width = 317
        Height = 21
        Align = alTop
        AutoScroll = False
        TabOrder = 0
        OnExit = edit_parameter_adjusted
        Description_label = 'Organic matter'
        Units_label = '%'
      end
      object trackbar_organic_matter: TTrackBar
        Left = 0
        Top = 21
        Width = 317
        Height = 43
        Align = alTop
        Max = 8
        Orientation = trHorizontal
        Frequency = 1
        Position = 0
        SelEnd = 0
        SelStart = 0
        TabOrder = 1
        ThumbLength = 15
        TickMarks = tmBottomRight
        TickStyle = tsAuto
        OnChange = trackbar_organic_matterChange
      end
      object edit_salinity: TAutoFloat32EditBar
        Left = 0
        Top = 64
        Width = 317
        Height = 21
        Align = alTop
        AutoScroll = False
        TabOrder = 2
        OnExit = edit_parameter_adjusted
        Description_label = 'Salinity'
        Units_label = '%'
      end
      object trackbar_salinity: TTrackBar
        Left = 0
        Top = 85
        Width = 317
        Height = 43
        Align = alTop
        Max = 20
        Orientation = trHorizontal
        Frequency = 5
        Position = 0
        SelEnd = 0
        SelStart = 0
        TabOrder = 3
        ThumbLength = 15
        TickMarks = tmBottomRight
        TickStyle = tsAuto
        OnChange = trackbar_salinityChange
      end
      object edit_gravel_pct_by_wt: TAutoFloat32EditBar
        Left = 0
        Top = 192
        Width = 317
        Height = 21
        Align = alTop
        AutoScroll = False
        TabOrder = 4
        OnExit = edit_parameter_adjusted
        Description_label = 'Gravel (% by weight)'
        Units_label = 'units'
      end
      object trackbar_gravel_ptc_by_wt: TTrackBar
        Left = 0
        Top = 213
        Width = 317
        Height = 43
        Align = alTop
        Max = 70
        Orientation = trHorizontal
        Frequency = 10
        Position = 0
        SelEnd = 0
        SelStart = 0
        TabOrder = 5
        ThumbLength = 15
        TickMarks = tmBottomRight
        TickStyle = tsAuto
        OnChange = trackbar_gravel_ptc_by_wtChange
      end
      object edit_gravel_pct_by_vol: TAutoFloat32EditBar
        Left = 0
        Top = 128
        Width = 317
        Height = 21
        Align = alTop
        AutoScroll = False
        TabOrder = 6
        OnExit = edit_parameter_adjusted
        Description_label = 'Gravel (% by volume)'
        Units_label = '%'
      end
      object trackbar_gravel_ptc_by_vol: TTrackBar
        Left = 0
        Top = 149
        Width = 317
        Height = 43
        Align = alTop
        Max = 50
        Orientation = trHorizontal
        Frequency = 10
        Position = 0
        SelEnd = 0
        SelStart = 0
        TabOrder = 7
        ThumbLength = 15
        TickMarks = tmBottomRight
        TickStyle = tsAuto
        OnChange = trackbar_gravel_ptc_by_volChange
      end
      object edit_compaction: TAutoFloat32EditBar
        Left = 0
        Top = 256
        Width = 317
        Height = 21
        Align = alTop
        AutoScroll = False
        TabOrder = 8
        OnExit = edit_parameter_adjusted
        Description_label = 'Compaction'
        Units_label = 'units'
      end
      object trackbar_compaction: TTrackBar
        Left = 0
        Top = 277
        Width = 317
        Height = 43
        Align = alTop
        Max = 130
        Min = 90
        Orientation = trHorizontal
        Frequency = 10
        Position = 90
        SelEnd = 0
        SelStart = 0
        TabOrder = 9
        ThumbLength = 15
        TickMarks = tmBottomRight
        TickStyle = tsAuto
        OnChange = trackbar_compactionChange
      end
    end
  end
  object panel_model: TPanel
    Left = 328
    Top = 320
    Width = 464
    Height = 25
    Alignment = taLeftJustify
    Anchors = [akLeft, akTop, akRight]
    Caption = '  Model'
    TabOrder = 6
    object combobox_pedotransfer_model: TComboBox
      Left = 70
      Top = 2
      Width = 392
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      ItemHeight = 13
      TabOrder = 0
      Text = 'Saxton & Rawls 2006 (unadjusted)'
      OnChange = combobox_pedotransfer_modelChange
      Items.Strings = (
        'Saxton, Rawls, Romberger, Papendick 1986'
        'Saxton & Rawls 2006 (unadjusted)'
        'Saxton & Rawls 2006 (effective)'
        '')
    end
  end
  object BitBtn1: TBitBtn
    Left = 655
    Top = 472
    Width = 65
    Height = 25
    Anchors = [akRight, akBottom]
    TabOrder = 0
    Kind = bkOK
  end
  object BitBtn2: TBitBtn
    Left = 727
    Top = 472
    Width = 65
    Height = 25
    Anchors = [akRight, akBottom]
    TabOrder = 1
    Kind = bkCancel
  end
end
