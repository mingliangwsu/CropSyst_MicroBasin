object soil_editor_form: Tsoil_editor_form
  Left = 0
  Top = 0
  Caption = 'soil_editor_form'
  ClientHeight = 876
  ClientWidth = 620
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnKeyPress = FormKeyPress
  PixelsPerInch = 96
  TextHeight = 13
  object ScrollBox1: TScrollBox
    Left = 0
    Top = 24
    Width = 620
    Height = 852
    VertScrollBar.Position = 2
    Align = alClient
    BevelInner = bvNone
    TabOrder = 0
    object groupbox_surface: TGroupBox
      Left = 0
      Top = 323
      Width = 599
      Height = 137
      Align = alBottom
      Caption = 'Surface'
      TabOrder = 0
      object water_vapor_conductance_atmosphere_note: TLabel
        Left = 32
        Top = 112
        Width = 236
        Height = 13
        Caption = '(This is used for the finite difference model only).'
      end
      object panel_albedo: TPanel
        Left = 136
        Top = 15
        Width = 409
        Height = 58
        BevelOuter = bvNone
        TabOrder = 0
      end
      object groupbox_albedo: TGroupBox
        Left = 2
        Top = 15
        Width = 595
        Height = 74
        Align = alTop
        Caption = 'Albedo'
        TabOrder = 1
        DesignSize = (
          595
          74)
        object edit_albedo_dry: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 9
          Top = 16
          Width = 488
          Height = 22
          Alignment = taLeftJustify
          Anchors = [akLeft, akTop, akRight]
          BevelOuter = bvNone
          Caption = 'dry'
          TabOrder = 0
          TabStop = True
        end
        object edit_albedo_wet: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 9
          Top = 39
          Width = 488
          Height = 22
          Alignment = taLeftJustify
          Anchors = [akLeft, akTop, akRight]
          BevelOuter = bvNone
          Caption = 'wet'
          TabOrder = 1
          TabStop = True
        end
        object panel_albedo_buttons: TPanel
          Left = 503
          Top = 15
          Width = 90
          Height = 57
          Align = alRight
          BevelOuter = bvNone
          TabOrder = 2
          object button_albedo_dark: TButton
            Left = 0
            Top = 0
            Width = 90
            Height = 18
            Align = alTop
            Caption = 'dark'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -9
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
            OnClick = button_albedo_darkClick
          end
          object button_albedo_med: TButton
            Left = 0
            Top = 18
            Width = 90
            Height = 18
            Align = alTop
            Caption = 'medium'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -9
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 1
            OnClick = button_albedo_medClick
          end
          object button_albedo_light: TButton
            Left = 0
            Top = 36
            Width = 90
            Height = 18
            Align = alTop
            Caption = 'light'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -9
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 2
            OnClick = button_albedo_lightClick
          end
        end
      end
      object edit_water_vapor_conductance_atmosphere_adj: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 92
        Width = 589
        Height = 22
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Water vapor conductance atmosphere adjustment'
        TabOrder = 2
        TabStop = True
      end
    end
    object groupbox_runoff: TGroupBox
      Left = 0
      Top = 460
      Width = 599
      Height = 272
      Align = alBottom
      Caption = 'Runoff'
      TabOrder = 1
      object GroupBox3: TGroupBox
        Left = 2
        Top = 15
        Width = 595
        Height = 162
        Align = alTop
        Caption = 'SCS curve number mode'
        TabOrder = 0
        object groupbox_curve_number_notes: TGroupBox
          Left = 362
          Top = 15
          Width = 231
          Height = 145
          Align = alRight
          Caption = 'Notes'
          TabOrder = 0
          object curve_number_note: TLabel
            Left = 2
            Top = 15
            Width = 227
            Height = 82
            Align = alTop
            AutoSize = False
            Caption = 
              'For either cascade or finite difference model with SCS curve num' +
              'ber runoff submodel selected in the simulation submodel options.' +
              '  Normally the SCS curve number is calculated for current condit' +
              'ions, but  can be overridden with nonzero values entered  below.'
            Color = clInfoBk
            ParentColor = False
            Transparent = False
            WordWrap = True
          end
          object Label2: TLabel
            Left = 2
            Top = 97
            Width = 227
            Height = 162
            Align = alTop
            AutoSize = False
            Caption = 
              'If the optional override values are left 0, CropSyst will calcul' +
              'ate the curve number for the respective condition.'
            Color = clInfoBk
            ParentColor = False
            Transparent = False
            WordWrap = True
            ExplicitLeft = 3
            ExplicitTop = 117
            ExplicitWidth = 209
          end
        end
        object panel_curve_number_fields: TPanel
          Left = 2
          Top = 15
          Width = 360
          Height = 145
          Align = alClient
          BevelOuter = bvNone
          TabOrder = 1
          object groupbox_hydrologic: TGroupBox
            Left = 0
            Top = 0
            Width = 360
            Height = 73
            Align = alTop
            Caption = 'Hydrologic'
            TabOrder = 0
            object radiogroup_hydro_group: TRNAutoRadioGroup
              Left = 2
              Top = 15
              Width = 78
              Height = 56
              Align = alLeft
              Caption = 'Group'
              Columns = 2
              Items.Strings = (
                'A'
                'B'
                'C'
                'D')
              TabOrder = 0
            end
            object radiogroup_hydro_condition: TRNAutoRadioGroup
              Left = 80
              Top = 15
              Width = 278
              Height = 56
              Align = alClient
              Caption = 'Condition'
              Items.Strings = (
                'Poor'
                'Fair'
                'Good')
              TabOrder = 1
            end
          end
          object GroupBox4: TGroupBox
            Left = 0
            Top = 79
            Width = 360
            Height = 66
            Align = alBottom
            Caption = 'Curve number overrides'
            Color = clBtnFace
            ParentBackground = False
            ParentColor = False
            TabOrder = 1
            object edit_fallow_curve: TRNAutoParameterEditBar
              AlignWithMargins = True
              Left = 5
              Top = 18
              Width = 350
              Height = 22
              Hint = 
                'Note that this overrides the curve number for fallow condition I' +
                'I, in all other cases the curve number is calculated.'
              Align = alTop
              Alignment = taLeftJustify
              BevelOuter = bvNone
              Caption = 'for fallow antecedent moisture condition II '
              TabOrder = 0
              TabStop = True
            end
            object edit_override_curve_number: TRNAutoParameterEditBar
              AlignWithMargins = True
              Left = 5
              Top = 46
              Width = 350
              Height = 22
              Align = alTop
              Alignment = taLeftJustify
              BevelOuter = bvNone
              Caption = 'for all other conditions'
              TabOrder = 1
              TabStop = True
            end
          end
        end
      end
      object groupbox_numerical_solution_mode: TGroupBox
        Left = 2
        Top = 182
        Width = 595
        Height = 88
        Align = alBottom
        Caption = 'Numerical solution mode'
        TabOrder = 1
        object numerical_note: TLabel
          Left = 2
          Top = 15
          Width = 591
          Height = 26
          Align = alTop
          AutoSize = False
          Caption = 
            'These parameters are relevant only to the finite difference mode' +
            'l with numerical solution runoff submodel as selected in the sim' +
            'ulation submodel options.'
          Color = clInfoBk
          ParentColor = False
          Transparent = False
          WordWrap = True
          ExplicitWidth = 733
        end
        object edit_surface_storage: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 61
          Width = 585
          Height = 22
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Surface storage'
          TabOrder = 0
          TabStop = True
        end
        object checkbox_compute_surface_storage: TRNAutoCheckBox
          Left = 2
          Top = 41
          Width = 591
          Height = 17
          Align = alTop
          Caption = 'Compute surface storage'
          Checked = True
          State = cbChecked
          TabOrder = 1
        end
      end
    end
    object groupbox_RUSLE: TGroupBox
      Left = 0
      Top = 732
      Width = 599
      Height = 88
      Align = alBottom
      Caption = 'Erosion (RUSLE)'
      TabOrder = 2
      object erosion_note: TLabel
        Left = 2
        Top = 71
        Width = 595
        Height = 30
        Align = alTop
        AutoSize = False
        Caption = 
          'When running GIS projects, steepness and slope length may be pro' +
          'vided from other database or map layers. Enter here the default ' +
          'values to use when GIS database is not available or when running' +
          ' individual scenarios.'
        Color = clInfoBk
        ParentColor = False
        Transparent = False
        WordWrap = True
        ExplicitTop = 59
        ExplicitWidth = 656
      end
      object edit_steepness: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 18
        Width = 589
        Height = 22
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Steepness'
        TabOrder = 0
        TabStop = True
      end
      object edit_slope_length: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 46
        Width = 589
        Height = 22
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Slope length'
        TabOrder = 1
        TabStop = True
      end
    end
    object edit_SLPF: TRNAutoParameterEditBar
      AlignWithMargins = True
      Left = 3
      Top = 823
      Width = 593
      Height = 22
      Hint = 
        'An empirical multiplier that adjusts daily canopy photosynthesis' +
        ' due to unknown soil factors such as aluminum toxicity or phosph' +
        'orus deficiency.'
      Align = alBottom
      Alignment = taLeftJustify
      BevelOuter = bvNone
      Caption = 'SLPF  Soil Photosythesis Factor (Only used with CropGro)'
      TabOrder = 3
      TabStop = True
    end
    object groupbox_soil_profile: TGroupBox
      Left = 0
      Top = -2
      Width = 599
      Height = 331
      Align = alTop
      Caption = 'Soil profile'
      TabOrder = 4
      object texture_grid: TAdvStringGrid
        Left = 2
        Top = 15
        Width = 595
        Height = 243
        Cursor = crDefault
        Align = alClient
        ColCount = 17
        DefaultRowHeight = 20
        DrawingStyle = gdsClassic
        RowCount = 21
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goDrawFocusSelected]
        ParentFont = False
        ScrollBars = ssBoth
        TabOrder = 0
        OnAutoInsertRow = texture_gridAutoInsertRow
        OnAutoDeleteRow = texture_gridAutoDeleteRow
        OnClipboardPaste = texture_gridClipboardPaste
        OnClipboardBeforePasteCell = texture_gridClipboardBeforePasteCell
        OnCellValidate = texture_gridCellValidate
        ActiveCellFont.Charset = DEFAULT_CHARSET
        ActiveCellFont.Color = clWindowText
        ActiveCellFont.Height = -11
        ActiveCellFont.Name = 'MS Sans Serif'
        ActiveCellFont.Style = [fsBold]
        AutoNumAlign = True
        AutoSize = True
        CellNode.TreeColor = clSilver
        ColumnHeaders.Strings = (
          'Layers'
          'Thickness\nm'
          'Sand\n%'
          'Clay\n%'
          'Silt\n%'
          'Layer\nbypass\n0-1'
          'Permanent\nwilt point\nm'#179'/m'#179
          'Field\ncapacity\nm'#179'/m'#179
          'Bulk\ndensity\ng/cm'#179
          'Vol WC at\n-1500\nm'#179'/m'#179
          'Vol WC at\n-33\nm'#179'/m'#179
          'Saturated\nhydr.conc.\nm/day'
          'Air entry\npotential\nJ/kg'
          'Campbell\nb'
          'Saturation\nm'#179'/m'#179'\n(Computed)'
          'Cation\nexchange\ncapacity'
          'pH'
          'Organic matter %')
        ControlLook.FixedGradientHoverFrom = clGray
        ControlLook.FixedGradientHoverTo = clWhite
        ControlLook.FixedGradientDownFrom = clGray
        ControlLook.FixedGradientDownTo = clSilver
        ControlLook.DropDownHeader.Font.Charset = DEFAULT_CHARSET
        ControlLook.DropDownHeader.Font.Color = clWindowText
        ControlLook.DropDownHeader.Font.Height = -11
        ControlLook.DropDownHeader.Font.Name = 'Tahoma'
        ControlLook.DropDownHeader.Font.Style = []
        ControlLook.DropDownHeader.Visible = True
        ControlLook.DropDownHeader.Buttons = <>
        ControlLook.DropDownFooter.Font.Charset = DEFAULT_CHARSET
        ControlLook.DropDownFooter.Font.Color = clWindowText
        ControlLook.DropDownFooter.Font.Height = -11
        ControlLook.DropDownFooter.Font.Name = 'Tahoma'
        ControlLook.DropDownFooter.Font.Style = []
        ControlLook.DropDownFooter.Visible = True
        ControlLook.DropDownFooter.Buttons = <>
        Filter = <>
        FilterDropDown.Font.Charset = DEFAULT_CHARSET
        FilterDropDown.Font.Color = clWindowText
        FilterDropDown.Font.Height = -11
        FilterDropDown.Font.Name = 'Tahoma'
        FilterDropDown.Font.Style = []
        FilterDropDownClear = '(All)'
        FixedColWidth = 40
        FixedRowHeight = 44
        FixedFont.Charset = DEFAULT_CHARSET
        FixedFont.Color = clWindowText
        FixedFont.Height = -11
        FixedFont.Name = 'Tahoma'
        FixedFont.Style = []
        FloatFormat = '%.3f'
        MouseActions.AllRowSize = True
        Navigation.AllowInsertRow = True
        Navigation.AllowDeleteRow = True
        Navigation.AdvanceOnEnter = True
        Navigation.AllowClipboardShortCuts = True
        Navigation.AllowSmartClipboard = True
        Navigation.AllowClipboardAlways = True
        Navigation.CursorWalkEditor = True
        Navigation.TabToNextAtEnd = True
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
        ShowDesignHelper = False
        Version = '6.0.4.2'
        ExplicitLeft = 0
        ExplicitTop = 16
        ExplicitWidth = 809
        ExplicitHeight = 267
        ColWidths = (
          40
          58
          36
          33
          26
          39
          64
          34
          31
          59
          59
          60
          54
          55
          62
          43
          25)
        RowHeights = (
          44
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20)
        object edit_soil_layers: TRNAutoIntegerEdit
          Left = 1
          Top = 18
          Width = 38
          Height = 24
          Alignment = taRightJustify
          Lines.Strings = (
            '0')
          TabOrder = 3
          OnExit = edit_soil_layersExit
        end
      end
      object panel_profile_notes: TPanel
        Left = 2
        Top = 258
        Width = 595
        Height = 71
        Align = alBottom
        BevelOuter = bvNone
        TabOrder = 1
        DesignSize = (
          595
          71)
        object default_label: TLabel
          Left = 8
          Top = 29
          Width = 73
          Height = 13
          Anchors = [akLeft, akBottom]
          AutoSize = False
          Caption = 'Default'
          Color = clFuchsia
          ParentColor = False
          Transparent = False
        end
        object computed_label: TLabel
          Left = 89
          Top = 29
          Width = 153
          Height = 13
          Anchors = [akLeft, akBottom]
          AutoSize = False
          Caption = 'Computed from entered  values'
          Color = clLime
          ParentColor = False
          Transparent = False
        end
        object user_label: TLabel
          Left = 9
          Top = 48
          Width = 73
          Height = 13
          Anchors = [akLeft, akBottom]
          AutoSize = False
          Caption = 'User specified'
          Color = clYellow
          ParentColor = False
          Transparent = False
        end
        object estimated_label: TLabel
          Left = 89
          Top = 48
          Width = 153
          Height = 13
          Anchors = [akLeft, akBottom]
          AutoSize = False
          Caption = 'Estimated from texture'
          Color = clAqua
          ParentColor = False
          Transparent = False
          OnClick = estimated_labelClick
        end
        object Label3: TLabel
          Left = 394
          Top = 6
          Width = 197
          Height = 26
          Anchors = [akRight, akBottom]
          Caption = 
            'It is recommended  to  use the  estimated Air  entry potential a' +
            'nd Campbell b values)'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlue
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          WordWrap = True
          ExplicitLeft = 625
        end
        object label_install_hydr_prop_calc: TLabel
          Left = 248
          Top = 29
          Width = 140
          Height = 33
          Anchors = [akLeft, akRight, akBottom]
          AutoSize = False
          Caption = 'Click here to install the Hydraulic Properties Calculator tool.'
          Color = clInfoBk
          ParentColor = False
          Transparent = False
          WordWrap = True
          OnClick = label_install_hydr_prop_calcClick
          ExplicitWidth = 239
        end
        object button_select_texture_triangle: TBitBtn
          Left = 406
          Top = 38
          Width = 185
          Height = 25
          Anchors = [akRight, akBottom]
          Caption = 'Reselect soil texture for current layer'
          TabOrder = 0
          OnClick = button_select_texture_triangleClick
        end
        object button_hydr_prop_calc: TButton
          Left = 248
          Top = 38
          Width = 152
          Height = 25
          Hint = 'Launches Dr. Saxton'#39's Hydraulic Properties Calculator'
          Anchors = [akLeft, akRight, akBottom]
          Caption = 'Hydraulic Properties Calculator'
          ParentShowHint = False
          ShowHint = True
          TabOrder = 1
          OnClick = button_hydr_prop_calcClick
        end
        object checkbox_fixed_evap: TRNAutoCheckBox
          Left = 16
          Top = 8
          Width = 374
          Height = 17
          Caption = 
            'Layer 1 thickess is a fixed evaporative layer depth (do not subd' +
            'ivide layer 1)'
          State = cbGrayed
          TabOrder = 2
        end
      end
    end
  end
  object panel_jump_to: TPanel
    Left = 0
    Top = 0
    Width = 620
    Height = 24
    Align = alTop
    Alignment = taLeftJustify
    BevelOuter = bvNone
    TabOrder = 1
    object Label1: TLabel
      AlignWithMargins = True
      Left = 3
      Top = 3
      Width = 38
      Height = 18
      Align = alLeft
      Caption = 'Jump to'
      ExplicitLeft = 0
      ExplicitTop = 2
    end
    object button_texture: TButton
      Left = 44
      Top = 0
      Width = 55
      Height = 24
      Align = alLeft
      Caption = 'Texture'
      TabOrder = 0
      OnClick = button_textureClick
    end
    object button_hydro_prop: TButton
      Left = 99
      Top = 0
      Width = 112
      Height = 24
      Align = alLeft
      Caption = 'Hydraulic properties'
      TabOrder = 1
      OnClick = button_hydro_propClick
    end
    object button_chemistry: TButton
      Left = 211
      Top = 0
      Width = 59
      Height = 24
      Align = alLeft
      Caption = 'Chemistry'
      TabOrder = 2
      OnClick = button_chemistryClick
    end
    object button_surface: TButton
      Left = 270
      Top = 0
      Width = 53
      Height = 24
      Align = alLeft
      Caption = 'Surface'
      TabOrder = 3
      OnClick = button_surfaceClick
    end
    object button_runoff: TButton
      Left = 323
      Top = 0
      Width = 49
      Height = 24
      Align = alLeft
      Caption = 'Runoff'
      TabOrder = 4
      OnClick = button_runoffClick
    end
    object button_erosion: TButton
      Left = 372
      Top = 0
      Width = 48
      Height = 24
      Align = alLeft
      Caption = 'Erosion'
      TabOrder = 5
      OnClick = button_erosionClick
    end
  end
end
