object soil_editor_form: Tsoil_editor_form
  Left = 65
  Top = -513
  Width = 691
  Height = 406
  Caption = 'Soil editor:'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poDesktopCenter
  OnKeyPress = FormKeyPress
  PixelsPerInch = 96
  TextHeight = 13
  object soil_pagecontrol: TPageControl
    Left = 0
    Top = 0
    Width = 683
    Height = 372
    ActivePage = profile_tabsheet
    Align = alClient
    TabOrder = 0
    object profile_tabsheet: TTabSheet
      Caption = 'Profile'
      ImageIndex = 3
      object default_label: TLabel
        Left = 8
        Top = 310
        Width = 73
        Height = 13
        Anchors = [akLeft, akBottom]
        AutoSize = False
        Caption = 'Default'
        Color = clFuchsia
        ParentColor = False
      end
      object estimated_label: TLabel
        Left = 88
        Top = 325
        Width = 153
        Height = 13
        Anchors = [akLeft, akBottom]
        AutoSize = False
        Caption = 'Estimated from texture'
        Color = clAqua
        ParentColor = False
        OnClick = estimated_label_onclick
      end
      object computed_label: TLabel
        Left = 88
        Top = 310
        Width = 153
        Height = 13
        Anchors = [akLeft, akBottom]
        AutoSize = False
        Caption = 'Computed from entered  values'
        Color = clLime
        ParentColor = False
      end
      object user_label: TLabel
        Left = 8
        Top = 325
        Width = 73
        Height = 13
        Anchors = [akLeft, akBottom]
        AutoSize = False
        Caption = 'User specified'
        Color = clYellow
        ParentColor = False
      end
      object jump_to_button: TLabel
        Left = 320
        Top = 0
        Width = 93
        Height = 13
        Caption = '<-- Focus to column'
      end
      object Label3: TLabel
        Left = 467
        Top = 285
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
      end
      object label_install_hydr_prop_calc: TLabel
        Left = 248
        Top = 309
        Width = 221
        Height = 33
        Anchors = [akLeft, akRight, akBottom]
        AutoSize = False
        Caption = 'Click here to install the Hydraulic Properties Calculator tool.'
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
        OnClick = label_install_hydr_prop_calcClick
      end
      object label_fine_soil_basis: TLabel
        Left = 4
        Top = 385
        Width = 663
        Height = 13
        Anchors = [akLeft, akTop, akRight]
        AutoSize = False
        Caption = 'Enter sand and clay as fine soil basis (excluding gravel).'
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
      end
      object checkbox_fixed_evap: TAutoCheckBox
        Left = 0
        Top = 286
        Width = 385
        Height = 24
        Hint = 'obsolete'
        Anchors = [akLeft, akBottom]
        Caption = 
          'obsolete Layer 1 thickess is a fixed evaporative layer depth (do' +
          ' not subdivide layer 1)'
        TabOrder = 0
        Visible = False
      end
      object texture_grid: TAdvStringGrid
        Left = 0
        Top = 16
        Width = 669
        Height = 228
        Cursor = crDefault
        Anchors = [akLeft, akTop, akRight, akBottom]
        ColCount = 17
        DefaultRowHeight = 20
        RowCount = 21
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goDrawFocusSelected, goEditing]
        ParentFont = False
        ScrollBars = ssBoth
        TabOrder = 1
        OnAutoInsertRow = texture_grid_onautoinsertrow
        OnAutoDeleteRow = texture_grid_onautodeleterow
        OnClipboardPaste = texture_gridClipboardPaste
        OnClipboardBeforePasteCell = texture_gridClipboardBeforePasteCell
        OnCellValidate = texture_grid_oncellvalidate
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
          'Permanent\nwilt point\nm³/m³'
          'Field\ncapacity\nm³/m³'
          'Bulk\ndensity\ng/cm³'
          'Water pot\n at FC\nkPa'
          ''
          'Saturated\nhydr.conc.\nm/day'
          'Air entry\npotential\nJ/kg'
          'Campbell\nb'
          'Saturation\nm³/m³\n(Computed)'
          'Cation\nexchange\ncapacity'
          'pH'
          'Organic matter %')
        Filter = <>
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
        ColWidths = (
          40
          66
          44
          41
          34
          47
          72
          42
          39
          67
          4
          68
          62
          63
          70
          51
          33)
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
      end
      object button_texture: TButton
        Left = 40
        Top = 0
        Width = 75
        Height = 17
        Caption = 'Texture'
        TabOrder = 2
        OnClick = button_texture_onclick
      end
      object button_hydro_prop: TButton
        Left = 122
        Top = 0
        Width = 105
        Height = 17
        Caption = 'Hydraulic properties'
        TabOrder = 3
        OnClick = button_hydro_propClick
      end
      object button_chemistry: TButton
        Left = 234
        Top = 0
        Width = 75
        Height = 17
        Caption = 'Chemistry'
        TabOrder = 4
        OnClick = button_chemistry_onclick
      end
      object button_select_texture_triangle: TBitBtn
        Left = 475
        Top = 317
        Width = 185
        Height = 25
        Anchors = [akRight, akBottom]
        Caption = 'Reselect soil texture for current layer'
        TabOrder = 5
        OnClick = button_select_texture_triangle_onclick
      end
      object button_hydr_prop_calc: TButton
        Left = 248
        Top = 317
        Width = 221
        Height = 25
        Hint = 'Launches Dr. Saxton'#39's Hydraulic Properties Calculator'
        Anchors = [akLeft, akRight, akBottom]
        Caption = 'Hydraulic Properties Calculator'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 6
        OnClick = button_hydr_prop_calcClick
      end
      object edit_soil_layers: TAutoInt16Edit
        Left = 3
        Top = 37
        Width = 38
        Height = 24
        Alignment = taRightJustify
        Lines.Strings = (
          '0')
        TabOrder = 7
        OnExit = edit_soil_layers_onexit
      end
      object GroupBox1: TGroupBox
        Left = 0
        Top = 243
        Width = 321
        Height = 65
        Anchors = [akLeft, akBottom]
        Caption = 'Evaporative layer thickness (meter)'
        TabOrder = 8
        object Label1: TLabel
          Left = 8
          Top = 16
          Width = 117
          Height = 13
          Caption = 'Cascade infilration model'
        end
        object Label4: TLabel
          Left = 8
          Top = 40
          Width = 141
          Height = 13
          Caption = 'Finite different infiltation model'
        end
        object edit_evaporative_layer_thickness_cascade: TAutoFloat32Edit
          Left = 240
          Top = 16
          Width = 70
          Height = 22
          Alignment = taRightJustify
          Anchors = [akTop, akRight]
          Lines.Strings = (
            '0.00')
          TabOrder = 0
        end
        object edit_evaporative_layer_thickness_finite_difference: TAutoFloat32Edit
          Left = 240
          Top = 40
          Width = 70
          Height = 22
          Alignment = taRightJustify
          Anchors = [akTop, akRight]
          Lines.Strings = (
            '0.00')
          TabOrder = 1
        end
      end
    end
    object surface_tabsheet: TTabSheet
      Caption = 'Surface'
      ImageIndex = 4
      object water_vapor_conductance_atmosphere_note: TLabel
        Left = 48
        Top = 120
        Width = 226
        Height = 13
        Caption = '(This is used for the finite difference model only).'
      end
      object edit_albedo_dry: TAutoFloat32EditBar
        Left = 16
        Top = 24
        Width = 329
        Height = 21
        AutoScroll = False
        TabOrder = 0
        Description_label = 'Albedo dry'
        Units_label = '(0-1)'
      end
      object edit_albedo_wet: TAutoFloat32EditBar
        Left = 16
        Top = 48
        Width = 329
        Height = 21
        AutoScroll = False
        TabOrder = 1
        Description_label = 'Albedo wet'
        Units_label = '(0-1)'
      end
      object edit_water_vapor_conductance_atmosphere_adj: TAutoFloat32EditBar
        Left = 16
        Top = 96
        Width = 489
        Height = 21
        AutoScroll = False
        TabOrder = 2
        Description_label = 'Water vapor conductance atmosphere adjustment'
        Units_label = '(0-1)'
      end
      object button_albedo_dark: TButton
        Left = 384
        Top = 24
        Width = 75
        Height = 17
        Caption = 'Dark'
        TabOrder = 3
        OnClick = button_albedo_dark_onclick
      end
      object button_albedo_med: TButton
        Left = 384
        Top = 40
        Width = 75
        Height = 17
        Caption = 'Medium'
        TabOrder = 4
        OnClick = button_albedo_medclick
      end
      object button_albedo_light: TButton
        Left = 384
        Top = 56
        Width = 75
        Height = 17
        Caption = 'Light'
        TabOrder = 5
        OnClick = albedo_light_button_onclick
      end
    end
    object runoff_tabsheet: TTabSheet
      Caption = 'Runoff'
      object curve_number_groupbox: TGroupBox
        Left = 0
        Top = 0
        Width = 675
        Height = 137
        Align = alTop
        Caption = 'SCS curve number mode'
        TabOrder = 0
        object edit_fallow_curve: TAutoInt16EditBar
          Left = 2
          Top = 81
          Width = 671
          Height = 22
          Hint = 
            'Note that this overrides the curve number for fallow condition I' +
            'I, in all other cases the curve number is calculated.'
          Align = alTop
          AutoScroll = False
          ParentShowHint = False
          ShowHint = True
          TabOrder = 0
          Description_label = 'SCS curve number for fallow antecedent moisture condition II '
          Units_label = 'units'
        end
        object panel_SCS_hydroXXX: TPanel
          Left = 2
          Top = 15
          Width = 671
          Height = 66
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 1
          object curve_number_note: TLabel
            Left = 220
            Top = 0
            Width = 277
            Height = 66
            Align = alLeft
            AutoSize = False
            Caption = 
              'For either cascade or finite difference model with SCS curve num' +
              'ber runoff submodel selected in the simulation submodel options.' +
              '  Normally the SCS curve number is calculated for current condit' +
              'ions, but  can be overridden with nonzero values entered  below'
            Color = clInfoBk
            ParentColor = False
            WordWrap = True
          end
          object Label2: TLabel
            Left = 552
            Top = 0
            Width = 119
            Height = 66
            Align = alRight
            AutoSize = False
            Caption = 
              'If the optional override values are left 0, CropSyst will calcul' +
              'ate the curve number for the respective condition.'
            Color = clInfoBk
            ParentColor = False
            WordWrap = True
          end
          object radiogroup_hydro_group: TAutoRadioGroup
            Left = 0
            Top = 0
            Width = 110
            Height = 66
            Align = alLeft
            Caption = 'Hydrologic group'
            Items.Strings = (
              'A'
              'B'
              'C'
              'D')
            TabOrder = 0
          end
          object radiogroup_hydro_condition: TAutoRadioGroup
            Left = 110
            Top = 0
            Width = 110
            Height = 66
            Align = alLeft
            Caption = 'Hydrologic condition'
            Items.Strings = (
              'Poor'
              'Fair'
              'Good')
            TabOrder = 1
          end
        end
        object edit_override_curve_number: TAutoInt16EditBar
          Left = 2
          Top = 103
          Width = 671
          Height = 22
          Align = alTop
          AutoScroll = False
          TabOrder = 2
          Description_label = 'SCS curve number override for all other conditions'
          Units_label = 'units'
        end
      end
      object numerical_groupbox: TGroupBox
        Left = 0
        Top = 137
        Width = 675
        Height = 104
        Align = alTop
        Caption = 'Numerical solution mode'
        TabOrder = 1
        object numerical_note: TLabel
          Left = 2
          Top = 15
          Width = 671
          Height = 58
          Align = alTop
          AutoSize = False
          Caption = 
            'These parameters are relevant only to the finite difference mode' +
            'l with numerical solution runoff submodel as selected in the sim' +
            'ulation submodel options.'
          Color = clInfoBk
          ParentColor = False
          WordWrap = True
        end
        object edit_surface_storage: TAutoFloat32EditBar
          Left = 2
          Top = 73
          Width = 671
          Height = 22
          Align = alTop
          AutoScroll = False
          TabOrder = 0
          Description_label = 'Surface storage'
          Units_label = 'mm'
        end
        object checkbox_compute_surface_storage: TAutoCheckBox
          Left = 8
          Top = 48
          Width = 624
          Height = 17
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Compute surface storage'
          Checked = True
          Color = clInfoBk
          ParentColor = False
          State = cbChecked
          TabOrder = 1
          OnClick = checkbox_compute_surface_storageClick
        end
      end
    end
    object erosion_tabsheet: TTabSheet
      Caption = 'Erosion'
      ImageIndex = 1
      object RUSLE_label: TLabel
        Left = 0
        Top = 0
        Width = 107
        Height = 13
        Align = alTop
        Caption = 'Parameters for RUSLE'
      end
      object erosion_note: TLabel
        Left = 0
        Top = 57
        Width = 675
        Height = 48
        Align = alTop
        AutoSize = False
        Caption = 
          'When running GIS projects, steepness and slope length may be pro' +
          'vided from other database or map layers. Enter here the default ' +
          'values to use when GIS database is not available or when running' +
          ' individual scenarios.'
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
      end
      object edit_steepness: TAutoFloat32EditBar
        Left = 0
        Top = 13
        Width = 675
        Height = 22
        Align = alTop
        AutoScroll = False
        TabOrder = 0
        Description_label = 'Steepness'
        Units_label = '% (1-100)'
      end
      object edit_slope_length: TAutoFloat32EditBar
        Left = 0
        Top = 35
        Width = 675
        Height = 22
        Align = alTop
        AutoScroll = False
        TabOrder = 1
        Description_label = 'Slope length'
        Units_label = 'm'
      end
    end
    object tabsheet_other: TTabSheet
      Caption = 'Other'
      ImageIndex = 4
      object edit_SLPF: TAutoFloat32EditBar
        Left = 0
        Top = 0
        Width = 675
        Height = 21
        Hint = 
          'An empirical multipliers that adjusts daily canopy photosynthesi' +
          's due to unknown soil factors such as aluminum toxicity or phosp' +
          'horus deficiency.'
        Align = alTop
        AutoScroll = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        Description_label = 'SLPF  Soil Photosythesis Factor'
        Units_label = 'units'
      end
    end
  end
  object BitBtn1: TBitBtn
    Left = 296
    Top = 0
    Width = 75
    Height = 25
    Caption = 'Place holder'
    TabOrder = 1
    Visible = False
  end
end
