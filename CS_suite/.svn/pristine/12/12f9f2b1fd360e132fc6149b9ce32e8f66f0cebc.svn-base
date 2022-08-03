object crop_editor_form: Tcrop_editor_form
  Left = 0
  Top = 0
  Caption = 'Crop:'
  ClientHeight = 595
  ClientWidth = 686
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Icon.Data = {
    0000010001002020100000000000E80200001600000028000000200000004000
    0000010004000000000080020000000000000000000000000000000000000000
    0000000080000080000000808000800000008000800080800000C0C0C0008080
    80000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00002A
    222CCCCCCC2A2CCCCCCCCCCB3CCC0222A2A2CCCA222AAC22ACCCCCCB3CCCA2A2
    22AA2CCC2ACA2A2CCCCCCCCBBCCCA22A22222CCCCCCA2CCCCCCCCCB3BCCCA222
    2A222C22CC2A22C22CCCCCBBBCCCA22A22AA2CCAC2AA2A22CCCCCC3B3CCCA22A
    22222CCC2ACA2CACCCCCCCBBCBCCCA22AA22CCCCCCCA2CCCCCCCCCB3CBCCCCA2
    222CCC2CCC2A2CCC2CCCCBCBC3CCCCCAAACCCC22C2AA22C22CCCC3CBCBCCCCCC
    CCCCCCCA2ACA2A22CCCCCBCBCCCCCCCCCCCCCCCCCCCA2CACCCCCCCCBCCCCCCCC
    CCCCCCCCCCCA2CCCCCCCCCCBCCCCCCCCCCCCCCCCCCCA2C22CCCCCCBBBCCCCCCC
    CCCCCCCA2C2A222CCCCCCCBBBCCCCCCCCCCCCCCC22A22ACCCCCCCCBBBCCCCCCC
    CCCCCCCCA2CACCCCCCCCCCCCCCCCCCCCCCCCCCC2CCC2CCC2CCCCCCCCCCCCCCCC
    CCCCCCCACC2ACCC2CCCCCCCCCCCCCCCCCCCCCCCC22C22C2CCCCCCCCCCCCCCCCC
    CCCCCCCCACCAA2ACCCCCCCCCCCCCCCCCCCCCCCCCCC22CCCCCCCCCCCCCCCCCCCC
    CCCCCCC2C2CACCCCCCCCCCCCCCCCCCCCCCCCCCCA2AC22CCCCCCCCCCCCCCCCCCC
    CCCCCCCCCCCAA22CCCCCCCCCCCCCCCCCCCCCCCCCCCC2CACCCCCCCCCCCCCCCCCC
    CCCCCCCCCCCBCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCBCCCCCCCCCCCCCCCCCCCC
    CCCCCCCCCCCBCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
    CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC000
    0000800000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    000000000000000000000000000000000000000000000000000000000000}
  OldCreateOrder = False
  OnActivate = FormActivate
  OnKeyPress = FormKeyPress
  PixelsPerInch = 96
  TextHeight = 13
  object scrollbox_parameters: TScrollBox
    Left = 177
    Top = 0
    Width = 509
    Height = 595
    VertScrollBar.Position = 2975
    Align = alClient
    BevelInner = bvNone
    BevelOuter = bvNone
    BorderStyle = bsNone
    TabOrder = 0
    ExplicitLeft = 192
    ExplicitWidth = 494
    object groupbox_classification: TGroupBox
      Left = 0
      Top = -2975
      Width = 492
      Height = 153
      Align = alTop
      Caption = 'Classification'
      TabOrder = 0
      object note_harvested_biomass: TLabel
        Left = 146
        Top = 87
        Width = 171
        Height = 42
        AutoSize = False
        Caption = 'Make sure to select the harvested biomass (not Unknown).'
        Color = clRed
        ParentColor = False
        WordWrap = True
      end
      object radiogroup_landuse: TRNAutoRadioGroup
        Left = 323
        Top = 6
        Width = 140
        Height = 81
        Caption = 'Land use'
        Items.Strings = (
          'Fallow or untilled rows'
          'Row crops'
          'Small grain'
          'Closed seed legumes'
          'Pasture')
        TabOrder = 0
      end
      object radiogroup_life_cycle: TRNAutoRadioGroup
        Left = 3
        Top = 16
        Width = 137
        Height = 71
        Caption = 'Life cycle'
        Items.Strings = (
          'Indeterminate'
          'Annual'
          'Biennial'
          'Perennial')
        TabOrder = 1
        OnClick = radiogroup_life_cycleClick
      end
      object radiogroup_photosynthetic: TRNAutoRadioGroup
        Left = 3
        Top = 87
        Width = 137
        Height = 58
        Caption = 'Photosynthetic pathway'
        Items.Strings = (
          'C3'
          'C4'
          'CAM')
        TabOrder = 2
      end
      object radiogroup_harvested_biomass: TRNAutoRadioGroup
        Left = 146
        Top = 6
        Width = 171
        Height = 81
        Caption = 'Harvested biomass'
        Columns = 2
        Items.Strings = (
          'Seed/ackene'
          'Root'
          'Tuber'
          'Leaf'
          'Fruit'
          'Canopy'
          'Everything'
          'Unknown')
        TabOrder = 3
        OnClick = radiogroup_harvested_biomassClick
      end
      object checkbox_grape: TRNAutoCheckBox
        Left = 154
        Top = 130
        Width = 55
        Height = 17
        Caption = 'Grape'
        State = cbGrayed
        TabOrder = 4
        OnClick = checkbox_grapeClick
      end
      object checkbox_tea: TRNAutoCheckBox
        Left = 238
        Top = 130
        Width = 53
        Height = 17
        Caption = 'Tea'
        State = cbGrayed
        TabOrder = 5
      end
      object radiogroup_stem_type: TRNAutoRadioGroup
        Left = 323
        Top = 87
        Width = 136
        Height = 63
        Caption = 'Stem type'
        Items.Strings = (
          'Herbaceous'
          'Woody')
        TabOrder = 6
      end
    end
    object groupbox_layout: TGroupBox
      Left = 0
      Top = -690
      Width = 492
      Height = 200
      Align = alTop
      Caption = 'Layout'
      TabOrder = 1
      object groupbox_orientation: TGroupBox
        Left = 2
        Top = 15
        Width = 488
        Height = 82
        Align = alTop
        Caption = 'Orientation'
        TabOrder = 0
        ExplicitWidth = 503
        object edit_tree_spacing: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 57
          Width = 478
          Height = 21
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Spacing within rows'
          TabOrder = 0
          ExplicitWidth = 493
        end
        object edit_row_spacing: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 36
          Width = 478
          Height = 21
          Hint = '0 = North, 90 = East, 180 = South,  270 = West'
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Spacing between rows'
          ParentShowHint = False
          ShowHint = True
          TabOrder = 1
          ExplicitWidth = 493
        end
        object edit_row_azimuth: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 15
          Width = 478
          Height = 21
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Row azimuth'
          ParentShowHint = False
          ShowHint = True
          TabOrder = 2
          ExplicitWidth = 493
        end
      end
      object groupbox_canopy_characteristics: TGroupBox
        Left = 2
        Top = 97
        Width = 488
        Height = 104
        Align = alTop
        Caption = 'Canopy characteristics'
        TabOrder = 1
        ExplicitWidth = 503
        object Label5: TLabel
          Left = 238
          Top = 0
          Width = 26
          Height = 13
          Caption = 'Initial'
        end
        object Label8: TLabel
          Left = 328
          Top = 0
          Width = 22
          Height = 13
          Caption = 'Final'
        end
        object edit_final_row_height: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 72
          Width = 478
          Height = 21
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Tree height'
          TabOrder = 0
          ExplicitWidth = 493
          object edit_initial_row_height: TRNAutoFloatEdit
            Left = 306
            Top = 0
            Width = 70
            Height = 21
            Margins.Top = 0
            Margins.Bottom = 0
            Align = alRight
            Alignment = taRightJustify
            Lines.Strings = (
              '0')
            TabOrder = 5
            ExplicitLeft = 321
          end
        end
        object edit_final_tree_breadth: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 45
          Width = 478
          Height = 21
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Tree width along the row '
          TabOrder = 1
          ExplicitWidth = 493
          object edit_initial_tree_breadth: TRNAutoFloatEdit
            Left = 306
            Top = 0
            Width = 70
            Height = 21
            Margins.Top = 0
            Margins.Bottom = 0
            Align = alRight
            Alignment = taRightJustify
            Lines.Strings = (
              '0')
            TabOrder = 5
            ExplicitLeft = 321
          end
        end
        object edit_final_row_width: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 18
          Width = 478
          Height = 21
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Tree width across row'
          TabOrder = 2
          ExplicitWidth = 493
          object edit_initial_row_width: TRNAutoFloatEdit
            Left = 306
            Top = 0
            Width = 70
            Height = 21
            Margins.Top = 0
            Margins.Bottom = 0
            Align = alRight
            Alignment = taRightJustify
            Lines.Strings = (
              '0')
            TabOrder = 5
            ExplicitLeft = 321
          end
        end
        object edit_branch_insertion_height: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 96
          Width = 478
          Height = 21
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Branch insertion height'
          TabOrder = 3
          ExplicitWidth = 493
        end
      end
    end
    object groupbox_hydrothermal_time: TGroupBox
      Left = 0
      Top = -456
      Width = 492
      Height = 146
      Align = alTop
      Caption = 'Hydrothermal time'
      TabOrder = 2
      object edit_b: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 120
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'b intercept for hydrothermal time constant curve'
        TabOrder = 0
        ExplicitWidth = 497
      end
      object edit_a: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 99
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'a intercept for hydrothermal time constant curve'
        TabOrder = 1
        ExplicitWidth = 497
      end
      object edit_stdev_base_soil_water_pot: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 78
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'StdDev base soil water potential'
        TabOrder = 2
        ExplicitWidth = 497
      end
      object edit_mean_base_soil_water_pot: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 57
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Mean base soil water potential for 50% emergence'
        TabOrder = 3
        ExplicitWidth = 497
      end
      object edit_germination_base_temperature: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 36
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Germination base temperature'
        TabOrder = 4
        ExplicitWidth = 497
      end
      object edit_seedling_leaf_area: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 15
        Width = 482
        Height = 21
        Hint = 'on first day of emergence'
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Seedling leaf area'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 5
        ExplicitWidth = 497
      end
    end
    object groupbox_thermal_time: TGroupBox
      Left = 0
      Top = -2822
      Width = 492
      Height = 104
      Margins.Top = 0
      Margins.Bottom = 0
      Align = alTop
      Caption = 'Thermal time accumulation'
      TabOrder = 3
      object radiogroup_resolution: TRNAutoRadioGroup
        Left = 2
        Top = 15
        Width = 68
        Height = 87
        Align = alLeft
        Caption = 'Resolution'
        Items.Strings = (
          'daily'
          'hourly')
        TabOrder = 0
        OnClick = radiogroup_resolutionClick
      end
      object panel_GGD_ranges: TPanel
        Left = 70
        Top = 15
        Width = 420
        Height = 87
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 1
        ExplicitWidth = 435
        object edit_base_temp: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 3
          Top = 0
          Width = 414
          Height = 21
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Base temperature'
          TabOrder = 0
          ExplicitWidth = 429
        end
        object edit_opt_temp: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 3
          Top = 21
          Width = 414
          Height = 21
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Optimal temperature'
          TabOrder = 1
          ExplicitWidth = 429
        end
        object edit_max_temp: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 3
          Top = 42
          Width = 414
          Height = 21
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Maximum temperature'
          TabOrder = 2
          ExplicitWidth = 429
        end
        object edit_cutoff_temp: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 3
          Top = 63
          Width = 414
          Height = 21
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Cutoff temperature'
          TabOrder = 3
          ExplicitWidth = 429
        end
      end
    end
    object groupbox_transpiration: TGroupBox
      Left = 0
      Top = -2488
      Width = 492
      Height = 241
      Align = alTop
      Caption = 'Transpiration'
      TabOrder = 4
      object edit_max_water_uptake_mm: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 99
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Maximum water uptake'
        TabOrder = 0
        ExplicitWidth = 497
      end
      object edit_wilt_leaf_water_pot: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 78
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Wilting leaf water potential'
        TabOrder = 1
        ExplicitWidth = 497
      end
      object edit_leaf_water_pot_stomatal_closure: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 57
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Leaf water potential at the onset of stomatal closure'
        TabOrder = 2
        ExplicitWidth = 497
      end
      object edit_ET_crop_coef: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 36
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Evapotranspiration crop coefficient at full canopy'
        TabOrder = 3
        ExplicitWidth = 497
      end
      object edit_kc: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 15
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Canopy extinction coefficient for total (global) solar radiation'
        TabOrder = 4
        ExplicitWidth = 497
      end
      object groupbox_max_water_uptake: TGroupBox
        Left = 2
        Top = 120
        Width = 488
        Height = 121
        Align = alTop
        Caption = 'Maximum water uptake'
        TabOrder = 5
        ExplicitWidth = 503
        object edit_max_water_upake_before_fruit: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 15
          Width = 478
          Height = 21
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'before fruiting'
          TabOrder = 0
          ExplicitWidth = 493
        end
        object edit_max_water_uptake_during_intial_fruit: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 36
          Width = 478
          Height = 21
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'during initial fruit filling'
          TabOrder = 1
          ExplicitWidth = 493
        end
        object edit_max_water_uptake_during_rapid_fruit: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 57
          Width = 478
          Height = 21
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'during rapid fruit filling'
          TabOrder = 2
          ExplicitWidth = 493
        end
        object edit_max_water_uptake_during_veraison: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 78
          Width = 478
          Height = 21
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'during veraison (if applicable)'
          TabOrder = 3
          ExplicitWidth = 493
        end
        object edit_max_water_uptake_after_maturity: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 99
          Width = 478
          Height = 21
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'after maturity'
          TabOrder = 4
          ExplicitWidth = 493
        end
      end
    end
    object groupbox_attainable_growth: TGroupBox
      Left = 0
      Top = 553
      Width = 492
      Height = 531
      Align = alTop
      Caption = 'Attainable growth'
      TabOrder = 5
      object groupbox_transpiration_dependent_growth: TGroupBox
        Left = 2
        Top = 15
        Width = 488
        Height = 186
        Align = alTop
        Caption = 'Transpiration dependent growth'
        TabOrder = 0
        ExplicitWidth = 503
        object checkbox_WUE_changes: TRNAutoCheckBox
          Left = 2
          Top = 15
          Width = 484
          Height = 17
          Align = alTop
          Caption = 
            'Water use efficiency may differ during vegetative growth and rep' +
            'roductive growth'
          State = cbGrayed
          TabOrder = 0
          ExplicitWidth = 499
        end
        object edit_WUE_change_deg_day: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 35
          Width = 478
          Height = 21
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Thermal time for change of water use efficiency'
          TabOrder = 1
          ExplicitWidth = 493
        end
        object radiogroup_WUE_submodel: TRNAutoRadioGroup
          Left = 2
          Top = 59
          Width = 484
          Height = 62
          Align = alTop
          Caption = 'Water use efficiency submodel'
          Items.Strings = (
            'Tanner && Sinclair'
            'FAO AquaCrop water productivity'
            'Transpiration Use Efficiency curve')
          TabOrder = 2
          OnClick = radiogroup_WUE_submodelClick
          ExplicitWidth = 499
        end
        object scrollbox_WUE: TScrollBox
          Left = 2
          Top = 121
          Width = 484
          Height = 64
          VertScrollBar.Position = 81
          Align = alTop
          BorderStyle = bsNone
          TabOrder = 3
          ExplicitWidth = 499
          object groupbox_tanner_sinclair: TGroupBox
            Left = 0
            Top = -81
            Width = 467
            Height = 41
            Align = alTop
            Caption = 'Tanner && Sinclair'
            TabOrder = 0
            ExplicitWidth = 482
            object edit_reference_biomass_transp_coef_0: TRNAutoParameterEditBar
              AlignWithMargins = True
              Left = 5
              Top = 18
              Width = 457
              Height = 21
              Hint = 'Biomass water ratio'
              Align = alTop
              Alignment = taLeftJustify
              BevelOuter = bvNone
              Caption = 'Above ground biomass transpiration coefficient (K) for annuals'
              TabOrder = 0
              ExplicitWidth = 472
              object edit_reference_biomass_transp_coef_vegetative_0: TRNAutoFloatEdit
                Left = 285
                Top = 0
                Width = 70
                Height = 21
                Hint = 'Transpiration coefficient during vegetative growth'
                Align = alRight
                Alignment = taRightJustify
                Lines.Strings = (
                  '0')
                TabOrder = 5
                ExplicitLeft = 300
              end
            end
          end
          object groupbox_aquacrop: TGroupBox
            Left = 0
            Top = -40
            Width = 467
            Height = 40
            Align = alTop
            Caption = 'FAO AquaCrop water productivity'
            TabOrder = 1
            ExplicitWidth = 482
            object edit_water_productivity: TRNAutoParameterEditBar
              AlignWithMargins = True
              Left = 5
              Top = 18
              Width = 457
              Height = 21
              Hint = 
                'FAO AquaCrop water productivity during reproductive growth (or t' +
                'hroughout the season depending on the WUE mode).'
              Align = alTop
              Alignment = taLeftJustify
              BevelOuter = bvNone
              Caption = 'Water productivity'
              TabOrder = 0
              ExplicitWidth = 472
              object edit_water_productivity_vegetative: TRNAutoFloatEdit
                Left = 285
                Top = 0
                Width = 70
                Height = 21
                Hint = 'Water productivity during vegetative growth'
                Align = alRight
                Alignment = taRightJustify
                Lines.Strings = (
                  '0')
                ParentShowHint = False
                ShowHint = True
                TabOrder = 5
                ExplicitLeft = 300
              end
            end
          end
          object groupbox_TUE_curve: TGroupBox
            Left = 0
            Top = 0
            Width = 467
            Height = 64
            Align = alTop
            Caption = 'Transpiration Use Efficiency curve'
            TabOrder = 2
            ExplicitWidth = 482
            object edit_TUE_scaling_coef: TRNAutoParameterEditBar
              AlignWithMargins = True
              Left = 5
              Top = 36
              Width = 457
              Height = 21
              Margins.Top = 0
              Margins.Bottom = 0
              Align = alTop
              Alignment = taLeftJustify
              BevelOuter = bvNone
              Caption = 'Scaling coefficient of TUE regression (power function)'
              TabOrder = 0
              ExplicitWidth = 472
              object edit_TUE_scaling_coef_vegetative: TRNAutoFloatEdit
                Left = 285
                Top = 0
                Width = 70
                Height = 21
                Hint = 'Scaling coefficient of TUE regression during vegetative growth'
                Align = alRight
                Alignment = taRightJustify
                Lines.Strings = (
                  '0')
                TabOrder = 5
                ExplicitLeft = 300
              end
            end
            object edit_TUE_at_1kPa_VPD: TRNAutoParameterEditBar
              AlignWithMargins = True
              Left = 5
              Top = 15
              Width = 457
              Height = 21
              Hint = 
                'Transpiration Use Efficiency during reproductive growth (or thro' +
                'ughout the season depending on the WUE mode).'
              Margins.Top = 0
              Margins.Bottom = 0
              Align = alTop
              Alignment = taLeftJustify
              BevelOuter = bvNone
              Caption = 'Transpiration Use Efficiency when VPD is at 1kPa'
              TabOrder = 1
              ExplicitWidth = 472
              object edit_TUE_at_1kPa_VPD_vegetative: TRNAutoFloatEdit
                Left = 285
                Top = 0
                Width = 70
                Height = 21
                Hint = 'Transpiration use efficiency during vegetative growth'
                Align = alRight
                Alignment = taRightJustify
                Lines.Strings = (
                  '0')
                TabOrder = 5
                ExplicitLeft = 300
              end
            end
          end
        end
      end
      object groupbox_seasonal_adjustment: TGroupBox
        Left = 2
        Top = 201
        Width = 488
        Height = 176
        Align = alTop
        Caption = 'Seasonal adjustment'
        TabOrder = 1
        ExplicitWidth = 503
        object Label9: TLabel
          Left = 2
          Top = 15
          Width = 484
          Height = 13
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Caption = 'The first season (sowing year) is not adjusted'
          ExplicitWidth = 220
        end
        object label_seasonal_adjustment: TLabel
          Left = 2
          Top = 133
          Width = 484
          Height = 42
          Align = alTop
          AutoSize = False
          Caption = 
            'In the case of perennials there may be a gradual change of bioma' +
            'ss production in successive seasons. Enter multiplier values bet' +
            'ween 0 and 1 to decrease growth, or values greater than 0 to inc' +
            'rease attainable growth.'
          Color = clInfoBk
          ParentColor = False
          Transparent = False
          WordWrap = True
          ExplicitWidth = 499
        end
        object edit_seasonal_adjustment_1: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 28
          Width = 478
          Height = 21
          Hint = 'Biomass adjustment'
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Season 1 (Not applicable season 1 is not adjusted)'
          TabOrder = 0
          ExplicitWidth = 493
        end
        object edit_seasonal_adjustment_2: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 49
          Width = 478
          Height = 21
          Hint = 'Biomass adjustment season 2'
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Season 2'
          TabOrder = 1
          ExplicitWidth = 493
        end
        object edit_seasonal_adjustment_3: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 70
          Width = 478
          Height = 21
          Hint = 'Biomass adjustment season 3'
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Season 3'
          TabOrder = 2
          ExplicitWidth = 493
        end
        object edit_seasonal_adjustment_4: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 91
          Width = 478
          Height = 21
          Hint = 'Biomass adjustment season 4'
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Season 4'
          TabOrder = 3
          ExplicitWidth = 493
        end
        object edit_seasonal_adjustment_5: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 112
          Width = 478
          Height = 21
          Hint = 'Biomass adjustment season 5 and any following seasons'
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Season 5 and all following seasons'
          TabOrder = 4
          ExplicitWidth = 493
        end
      end
      object groupbox_radiation_dependent_growth: TGroupBox
        Left = 2
        Top = 377
        Width = 488
        Height = 136
        Align = alTop
        Caption = 'Radiation dependent growth'
        TabOrder = 2
        ExplicitWidth = 503
        object edit_opt_temp_for_growth: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 15
          Width = 478
          Height = 21
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Mean daily temperature that limits early growth'
          TabOrder = 0
          ExplicitWidth = 493
        end
        object radiogroup_max_RUE_mode: TRNAutoRadioGroup
          Left = 2
          Top = 55
          Width = 484
          Height = 37
          Align = alTop
          Caption = 'Radiation dependent growth based on'
          Columns = 2
          Items.Strings = (
            'Total radiation'
            'Photosynthetically Active Radiation')
          TabOrder = 1
          OnClick = radiogroup_max_RUE_modeClick
          ExplicitWidth = 499
        end
        object edit_max_RUE_total: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 92
          Width = 478
          Height = 21
          Hint = 'Radiation use efficiency'
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 
            'Maximum Radiation Use Efficiency (unstressed, low vapor pressure' +
            ' deficit)'
          TabOrder = 2
          ExplicitWidth = 493
        end
        object edit_max_RUE_PAR: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 113
          Width = 478
          Height = 21
          Hint = 'Radiation use efficiency'
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 
            'Maximum Radiation Use Efficiency (unstressed, low vapor pressure' +
            ' deficit) PAR'
          TabOrder = 3
          ExplicitWidth = 493
        end
        object label_must_not_be_less_than_base_temperature: TPanel
          Left = 2
          Top = 36
          Width = 484
          Height = 19
          Align = alTop
          BevelOuter = bvNone
          Caption = 
            'Growth limiting temperature must not be less than the thermal ti' +
            'me accumulation base temperature.'
          TabOrder = 4
          ExplicitWidth = 499
        end
      end
    end
    object groupbox_canopy: TGroupBox
      Left = 0
      Top = 327
      Width = 492
      Height = 226
      Align = alTop
      Caption = 'Canopy growth'
      TabOrder = 6
      object radiogroup_canopy_growth: TRNAutoRadioGroup
        Left = 2
        Top = 15
        Width = 488
        Height = 33
        Align = alTop
        Caption = 'Model'
        Columns = 2
        Items.Strings = (
          'Leaf Area Index based'
          'Canopy cover based')
        TabOrder = 0
        OnClick = radiogroup_canopy_growthClick
        ExplicitWidth = 503
      end
      object ScrollBox2: TScrollBox
        Left = 2
        Top = 48
        Width = 488
        Height = 134
        Align = alClient
        BevelEdges = []
        BevelInner = bvNone
        BevelOuter = bvNone
        BorderStyle = bsNone
        TabOrder = 1
        ExplicitWidth = 503
        object panel_leaf_area_index_based: TPanel
          Left = 0
          Top = 152
          Width = 471
          Height = 129
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 0
          ExplicitWidth = 486
          object edit_initial_GAI: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 3
            Top = 0
            Width = 465
            Height = 21
            Margins.Top = 0
            Margins.Bottom = 0
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Initial green leaf area index'
            TabOrder = 0
            ExplicitWidth = 480
          end
          object edit_regrowth_GAI: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 3
            Top = 21
            Width = 465
            Height = 21
            Hint = 
              'When there are clipping events or the crop comes out stress or d' +
              'ormancy conditions.this is the minimal green leaf area index ava' +
              'ilable to restart growth. Applies to perennial and/or clipped an' +
              'nuals'
            Margins.Top = 0
            Margins.Bottom = 0
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 
              'Min. green leaf area index for regrowth (perennial and/or clippe' +
              'd annuals)'
            TabOrder = 1
            ExplicitWidth = 480
          end
          object edit_max_LAI: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 3
            Top = 42
            Width = 465
            Height = 21
            Hint = 'For fruit tree crops, GAI will be limited to this value. For ot'
            Margins.Top = 0
            Margins.Bottom = 0
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Maximum expected leaf area index (required for fruit trees)'
            TabOrder = 2
            ExplicitWidth = 480
          end
          object edit_specific_leaf_area: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 3
            Top = 63
            Width = 465
            Height = 21
            Margins.Top = 0
            Margins.Bottom = 0
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Specific leaf area at optimum temperature'
            TabOrder = 3
            ExplicitWidth = 480
          end
          object edit_fract_LAI_mature: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 3
            Top = 84
            Width = 465
            Height = 21
            Margins.Top = 0
            Margins.Bottom = 0
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Fraction of max. LAI at physiological maturity'
            TabOrder = 4
            ExplicitWidth = 480
          end
          object edit_stem_leaf_partition: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 3
            Top = 105
            Width = 465
            Height = 21
            Margins.Top = 0
            Margins.Bottom = 0
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Stem/leaf partition coefficient'
            TabOrder = 5
            ExplicitWidth = 480
          end
        end
        object panel_canopy_cover_based: TPanel
          Left = 0
          Top = 0
          Width = 471
          Height = 152
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 1
          ExplicitWidth = 486
          object edit_canopy_cover_initial: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 3
            Top = 0
            Width = 465
            Height = 21
            Margins.Top = 0
            Margins.Bottom = 0
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Initial canopy cover'
            TabOrder = 0
            ExplicitWidth = 480
          end
          object edit_canopy_cover_maximum: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 3
            Top = 21
            Width = 465
            Height = 21
            Margins.Top = 0
            Margins.Bottom = 0
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Maximum canopy cover'
            TabOrder = 1
            ExplicitWidth = 480
          end
          object edit_canopy_cover_green_mature: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 3
            Top = 42
            Width = 465
            Height = 21
            Margins.Top = 0
            Margins.Bottom = 0
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Green canopy cover at maturity'
            TabOrder = 2
            ExplicitWidth = 480
          end
          object edit_canopy_cover_total_mature: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 3
            Top = 63
            Width = 465
            Height = 21
            Margins.Top = 0
            Margins.Bottom = 0
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Total canopy cover at maturity  (green and senesced)'
            TabOrder = 3
            ExplicitWidth = 480
          end
          object edit_RTT_at_half_CCmax: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 3
            Top = 84
            Width = 465
            Height = 21
            Margins.Top = 0
            Margins.Bottom = 0
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Relative thermal time at half maximum canopy cover'
            TabOrder = 4
            ExplicitWidth = 480
          end
          object edit_begin_senescence_deg_day: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 3
            Top = 105
            Width = 465
            Height = 21
            Margins.Top = 0
            Margins.Bottom = 0
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Begin senescence (thermal time)'
            TabOrder = 5
            ExplicitWidth = 480
          end
        end
      end
      object edit_LWP_that_reduces_canopy_expansion: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 182
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alBottom
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Leaf water potential that begins reduction of canopy expansion'
        TabOrder = 2
        ExplicitWidth = 497
      end
      object edit_LWP_that_stops_canopy_expansion: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 203
        Width = 482
        Height = 21
        Hint = 'Must be more negative than value above that begins reduction'
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alBottom
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Leaf water potential that stops canopy expansion'
        TabOrder = 3
        ExplicitWidth = 497
      end
    end
    object groupbox_phenology: TGroupBox
      Left = 0
      Top = 76
      Width = 492
      Height = 251
      Margins.Top = 0
      Margins.Bottom = 0
      Align = alTop
      Caption = 'Phenology'
      TabOrder = 7
      object Panel1: TPanel
        Left = 2
        Top = 15
        Width = 488
        Height = 25
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Thermal time to reach:'
        TabOrder = 0
        ExplicitWidth = 503
        object checkbox_clipping_resets: TRNAutoCheckBox
          AlignWithMargins = True
          Left = 329
          Top = 3
          Width = 156
          Height = 19
          Hint = 
            'If enabled, clipping events will reset active growth stage (use ' +
            'for perennials, such as alfalfa, grass and other fodder crops)'
          Align = alRight
          Anchors = [akTop, akBottom]
          Caption = 'Clipping resets active growth'
          ParentShowHint = False
          ShowHint = True
          State = cbGrayed
          TabOrder = 0
          ExplicitLeft = 344
        end
      end
      object edit_phenologic_sensitivity_water_stress: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 227
        Width = 482
        Height = 21
        Hint = '0 indicates no effect, 1 indicates full effect.'
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Adjustment factor for phenologic response to stress'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        ExplicitWidth = 497
      end
      object edit_deg_day_begin_maturity: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 206
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Physiological maturity'
        TabOrder = 2
        ExplicitWidth = 497
      end
      object edit_deg_day_begin_rapid_fruit_growth: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 166
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Begin rapid fruit growth'
        TabOrder = 3
        ExplicitWidth = 497
      end
      object edit_deg_day_begin_filling_grain_or_fruit: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 145
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 
          'Begin filling (seed filling, or orchard fruit filling, or tuber ' +
          'bulking)'
        TabOrder = 4
        ExplicitWidth = 497
      end
      object edit_deg_day_begin_flower: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 124
        Width = 482
        Height = 21
        Hint = 'If this is not a flowering crop, enter a very large number.'
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Begin flowering'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 5
        ExplicitWidth = 497
      end
      object edit_deg_day_end_vegetative_growth: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 103
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'End vegetative growth'
        TabOrder = 6
        ExplicitWidth = 497
      end
      object edit_max_root_depth_dd: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 82
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Maximum root depth achieved'
        TabOrder = 7
        ExplicitWidth = 497
      end
      object edit_deg_day_tuber_initiation: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 61
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Begin tuber initiation'
        TabOrder = 8
        ExplicitWidth = 497
      end
      object edit_deg_day_emerge: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 40
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Emergence / Start of shoot growth'
        TabOrder = 9
        ExplicitWidth = 497
      end
      object panel_maturity_significant: TPanel
        Left = 2
        Top = 187
        Width = 488
        Height = 19
        Align = alTop
        Alignment = taRightJustify
        BevelOuter = bvNone
        Caption = '(applicable to annual crop and fruit trees and not perennials)'
        TabOrder = 10
        ExplicitWidth = 503
        object checkbox_maturity_significant: TRNAutoCheckBox
          Left = 0
          Top = 0
          Width = 156
          Height = 19
          Align = alLeft
          Caption = 'Maturity is significant'
          State = cbGrayed
          TabOrder = 0
          OnClick = checkbox_maturity_significantClick
        end
      end
    end
    object groupbox_vernalization: TGroupBox
      Left = 0
      Top = -2611
      Width = 492
      Height = 123
      Align = alTop
      TabOrder = 8
      DesignSize = (
        492
        123)
      object checkbox_vernalization: TRNAutoCheckBox
        Left = 6
        Top = 0
        Width = 484
        Height = 17
        Anchors = [akLeft, akTop, akRight]
        Caption = 'Vernalization'
        State = cbGrayed
        TabOrder = 0
        OnClick = checkbox_vernalizationClick
        ExplicitWidth = 499
      end
      object edit_vern_end: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 78
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Vernalization days required to complete vernalization'
        TabOrder = 1
        ExplicitWidth = 497
      end
      object edit_vern_start: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 57
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Vernalization days to enable vernalization '
        TabOrder = 2
        ExplicitWidth = 497
      end
      object edit_vern_high_temp: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 36
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'High temperature for optimal vernalization'
        TabOrder = 3
        ExplicitWidth = 497
      end
      object edit_vern_low_temp: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 15
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Low temperature for optimal vernalization'
        TabOrder = 4
        ExplicitWidth = 497
      end
      object edit_vern_min_factor: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 99
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        AutoSize = True
        BevelOuter = bvNone
        Caption = 'Minimum vernalization factor'
        TabOrder = 5
        ExplicitWidth = 497
      end
    end
    object groupbox_root: TGroupBox
      Left = 0
      Top = -1092
      Width = 492
      Height = 129
      Align = alTop
      Caption = 'Root'
      TabOrder = 9
      object edit_at_pt_root_limit: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 99
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Act. to pot. transpiration ratio that limits root growth'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        ExplicitWidth = 497
      end
      object edit_root_density_distribution_curvature: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 78
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Curvature of root density distribution'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        ExplicitWidth = 497
      end
      object edit_surface_root_density: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 57
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Maximum surface root density'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 2
        ExplicitWidth = 497
      end
      object edit_root_length_per_unit_mass: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 36
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Root length per unit root mass'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 3
        ExplicitWidth = 497
      end
      object edit_max_root_depth: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 15
        Width = 482
        Height = 21
        Hint = 'Established root depth for established fruit trees'
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Maximum root depth'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 4
        ExplicitWidth = 497
      end
    end
    object groupbox_harvest: TGroupBox
      Left = 0
      Top = -963
      Width = 492
      Height = 273
      Align = alTop
      Caption = 'Harvest'
      TabOrder = 10
      object edit_HI_growth_sensitivity: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 36
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Sensitivity to water and nitrogen stress during active growth'
        TabOrder = 0
        ExplicitWidth = 497
      end
      object edit_HI_unstressed: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 15
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Unstressed harvest index'
        TabOrder = 1
        ExplicitWidth = 497
      end
      object PageControl1: TPageControl
        Left = 2
        Top = 57
        Width = 488
        Height = 216
        ActivePage = tabsheet_harvest_fruit
        Align = alTop
        TabOrder = 2
        ExplicitWidth = 503
        object tabsheet_harvest_grain: TTabSheet
          Caption = 'Grain'
          ExplicitWidth = 495
          object groupbox_harvest_sensitivity: TGroupBox
            Left = 0
            Top = 0
            Width = 480
            Height = 65
            Align = alTop
            Caption = 'Sensitivity to water and nitrogen stress during'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
            ExplicitWidth = 495
            object edit_HI_filling_sensitivity: TRNAutoParameterEditBar
              AlignWithMargins = True
              Left = 5
              Top = 45
              Width = 470
              Height = 21
              Align = alTop
              Alignment = taLeftJustify
              BevelOuter = bvNone
              Caption = 'filling/bulking'
              TabOrder = 0
              ExplicitWidth = 485
            end
            object edit_HI_flowering_sensitivity: TRNAutoParameterEditBar
              AlignWithMargins = True
              Left = 5
              Top = 18
              Width = 470
              Height = 21
              Align = alTop
              Alignment = taLeftJustify
              BevelOuter = bvNone
              Caption = 'flowering'
              TabOrder = 1
              ExplicitWidth = 485
            end
          end
          object edit_grain_translocation_factor: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 3
            Top = 149
            Width = 474
            Height = 21
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Translocation factor'
            TabOrder = 1
            ExplicitWidth = 489
          end
          object RNAutoParameterEditBar4: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 3
            Top = 122
            Width = 474
            Height = 21
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'during grain filling'
            TabOrder = 2
            ExplicitWidth = 489
          end
          object edit_HI_flowering_temperature_sensitivity: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 3
            Top = 95
            Width = 474
            Height = 21
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Temperature stress sensitivity during flowering'
            TabOrder = 3
            ExplicitWidth = 489
          end
          object edit_HI_filling_duration: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 3
            Top = 68
            Width = 474
            Height = 21
            Hint = 'Intended for climate change scenarios.'
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Duration of grain filling period (unstressed)'
            TabOrder = 4
            ExplicitWidth = 489
          end
        end
        object tabsheet_harvest_tuber: TTabSheet
          Caption = 'Tuber'
          ImageIndex = 1
          ExplicitWidth = 495
          object Label6: TLabel
            Left = 0
            Top = 0
            Width = 480
            Height = 13
            Align = alTop
            Caption = 'Sensitivity to water and nitrogen stress'
            ExplicitWidth = 189
          end
          object edit_HI_tuber_init_sensitivity: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 3
            Top = 16
            Width = 474
            Height = 21
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'during tuber initiation'
            TabOrder = 0
            ExplicitWidth = 489
          end
          object edit_HI_tuber_growth_sensitivity: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 3
            Top = 43
            Width = 474
            Height = 21
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'during tuber growth'
            TabOrder = 1
            ExplicitWidth = 489
          end
        end
        object tabsheet_harvest_fruit: TTabSheet
          Caption = 'tabsheet_harvest_fruit'
          ImageIndex = 2
          ExplicitWidth = 495
          object edit_harvest_temperature: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 3
            Top = 81
            Width = 474
            Height = 21
            Margins.Top = 0
            Margins.Bottom = 0
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Harvest temperature'
            TabOrder = 0
            ExplicitWidth = 489
          end
          object edit_harvest_temperature_days: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 3
            Top = 102
            Width = 474
            Height = 21
            Margins.Top = 0
            Margins.Bottom = 0
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Harvest temperature days'
            TabOrder = 1
            ExplicitWidth = 489
          end
          object radiogroup_fruit_harvest_condition: TRNAutoRadioGroup
            Left = 0
            Top = 0
            Width = 480
            Height = 81
            Align = alTop
            Caption = 'Harvest conditions'
            Items.Strings = (
              'Harvest is scheduled in management file'
              'Harvest on a fixed date'
              
                'Harvest between specified dates considering minimum air temperat' +
                'ure'
              
                'Harvest between specified dates considering average air temperat' +
                'ure')
            TabOrder = 2
            ExplicitWidth = 495
          end
          object groupbox_harvest_DOY: TGroupBox
            Left = 0
            Top = 123
            Width = 480
            Height = 62
            Align = alTop
            Caption = 'Harvest day of year'
            TabOrder = 3
            ExplicitWidth = 495
            object edit_harvest_DOY_earliest: TRNAutoParameterEditBar
              AlignWithMargins = True
              Left = 5
              Top = 15
              Width = 470
              Height = 21
              Margins.Top = 0
              Margins.Bottom = 0
              Align = alTop
              Alignment = taLeftJustify
              BevelOuter = bvNone
              Caption = 'earliest'
              TabOrder = 0
              ExplicitWidth = 485
            end
            object edit_harvest_DOY_latest: TRNAutoParameterEditBar
              AlignWithMargins = True
              Left = 5
              Top = 36
              Width = 470
              Height = 21
              Margins.Top = 0
              Margins.Bottom = 0
              Align = alTop
              Alignment = taLeftJustify
              BevelOuter = bvNone
              Caption = 'latest'
              TabOrder = 1
              ExplicitWidth = 485
            end
          end
        end
      end
    end
    object groupbox_dormancy: TGroupBox
      Left = 0
      Top = -310
      Width = 492
      Height = 347
      Align = alTop
      Caption = 'Dormancy/Seasonal'
      TabOrder = 11
      DesignSize = (
        492
        347)
      object pagecontrol_season_dormancy_mode: TPageControl
        Left = 2
        Top = 15
        Width = 488
        Height = 194
        ActivePage = tabsheet_dormancy
        Align = alClient
        Style = tsButtons
        TabOrder = 0
        OnChange = pagecontrol_season_dormancy_modeChange
        ExplicitWidth = 503
        object tabsheet_single_season: TTabSheet
          Caption = 'Single season'
          ExplicitWidth = 495
          object label_single_season_mode_1: TLabel
            Left = 0
            Top = 0
            Width = 480
            Height = 33
            Align = alTop
            AutoSize = False
            Caption = 
              'This mode is most commonly used for annual, biennial or (sometim' +
              'es) perennial crops that are not allowed to (or cannot) grow to ' +
              'a second season.  This mode is also usually used for winter crop' +
              's.'
            Color = clInfoBk
            ParentColor = False
            Transparent = False
            WordWrap = True
            ExplicitWidth = 538
          end
          object label_single_season_mode_2: TLabel
            Left = 0
            Top = 33
            Width = 480
            Height = 33
            Align = alTop
            AutoSize = False
            Caption = 
              'This mode is has no additional parameters and the crop tends to ' +
              'remain in maturity until harvest.'
            Color = clInfoBk
            ParentColor = False
            Transparent = False
            WordWrap = True
            ExplicitWidth = 538
          end
        end
        object tabsheet_multiple_season: TTabSheet
          Caption = 'Multiple season'
          ImageIndex = 1
          ExplicitWidth = 495
          object label_multiple_season_mode_1: TLabel
            Left = 0
            Top = 0
            Width = 480
            Height = 33
            Align = alTop
            AutoSize = False
            Caption = 
              'This mode is use for biennial or perennial crops or plants that ' +
              'can propogate themselves and tend to persist for multiple season' +
              's (I.e. grasses).'
            Color = clInfoBk
            ParentColor = False
            Transparent = False
            WordWrap = True
            ExplicitWidth = 538
          end
          object label_multiple_season_mode_2: TLabel
            Left = 0
            Top = 33
            Width = 480
            Height = 33
            Align = alTop
            AutoSize = False
            Caption = 
              'Plants may go into a state of inactivity (but not necessarily do' +
              'rmancy) that typifies the end of the season.'
            Color = clInfoBk
            ParentColor = False
            Transparent = False
            WordWrap = True
            ExplicitWidth = 538
          end
        end
        object tabsheet_dormancy: TTabSheet
          Caption = 'tabsheet_dormancy'
          ImageIndex = 2
          ExplicitWidth = 495
          object label_dormancy_mode: TLabel
            Left = 0
            Top = 0
            Width = 480
            Height = 41
            Align = alTop
            AutoSize = False
            Caption = 
              'Dormancy is important for perennials, biannuals, and orchard/vin' +
              'eyard fruits, but may be applicable to certain other crops as we' +
              'll.  Plants will become inactive so the inactive period paramete' +
              'rs are significant.'
            Color = clInfoBk
            ParentColor = False
            Transparent = False
            WordWrap = True
            ExplicitWidth = 467
          end
          object groupbox_chill_requirements: TGroupBox
            Left = 0
            Top = 62
            Width = 480
            Height = 101
            Align = alClient
            Caption = 'Chill requirements for fruit trees'
            TabOrder = 0
            ExplicitWidth = 495
            object edit_chill_threshold: TRNAutoParameterEditBar
              AlignWithMargins = True
              Left = 5
              Top = 78
              Width = 470
              Height = 21
              Margins.Top = 0
              Margins.Bottom = 0
              Align = alTop
              Alignment = taLeftJustify
              BevelOuter = bvNone
              Caption = 'Threshold temperature for chill requirement (not currently used)'
              TabOrder = 0
              ExplicitWidth = 485
            end
            object edit_deg_day_bud_break_chill_req_not_sat: TRNAutoParameterEditBar
              AlignWithMargins = True
              Left = 5
              Top = 36
              Width = 470
              Height = 21
              Margins.Top = 0
              Margins.Bottom = 0
              Align = alTop
              Alignment = taLeftJustify
              BevelOuter = bvNone
              Caption = 'Thermal time to bud break (chill requirement not satisfied)'
              TabOrder = 1
              ExplicitWidth = 485
            end
            object edit_deg_day_bud_break_chill_req_sat: TRNAutoParameterEditBar
              AlignWithMargins = True
              Left = 5
              Top = 15
              Width = 470
              Height = 21
              Margins.Top = 0
              Margins.Bottom = 0
              Align = alTop
              Alignment = taLeftJustify
              BevelOuter = bvNone
              Caption = 'Thermal time to bud break (chill requirement satisfied)'
              TabOrder = 2
              ExplicitWidth = 485
            end
            object edit_chill_requirement: TRNAutoParameterEditBar
              AlignWithMargins = True
              Left = 5
              Top = 57
              Width = 470
              Height = 21
              Margins.Top = 0
              Margins.Bottom = 0
              Align = alTop
              Alignment = taLeftJustify
              BevelOuter = bvNone
              Caption = 'Chill requirement'
              TabOrder = 3
              ExplicitWidth = 485
            end
          end
          object edit_dormancy_senesce: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 3
            Top = 41
            Width = 474
            Height = 21
            Hint = 
              'For perennial crops that hold on to canopy biomass through winte' +
              'r.  Use 100% if there is full leaf drop.'
            Margins.Top = 0
            Margins.Bottom = 0
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Biomass that senesces at the onset of dormancy'
            ParentShowHint = False
            ShowHint = True
            TabOrder = 1
            ExplicitWidth = 489
          end
        end
      end
      object groupbox_inactive_period: TGroupBox
        Left = 2
        Top = 209
        Width = 488
        Height = 136
        Align = alBottom
        Caption = 'Inactive period'
        TabOrder = 1
        ExplicitWidth = 503
        object label_inactivity_days_note: TLabel
          Left = 2
          Top = 15
          Width = 484
          Height = 26
          Align = alTop
          Caption = 
            'Number of days of consecutive of average daily temperature below' +
            ' the inducement temperature that identifies'
          WordWrap = True
          ExplicitWidth = 490
        end
        object edit_consider_inactive_days: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 41
          Width = 478
          Height = 21
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'at end or restart of growth activity'
          TabOrder = 0
          ExplicitWidth = 493
        end
        object edit_inducement_temperature: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 62
          Width = 478
          Height = 21
          Hint = 
            'Average temperature over these consecutive days below which inac' +
            'tivity is induced'
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'edit_inducement_temperature'
          ParentShowHint = False
          ShowHint = True
          TabOrder = 1
          ExplicitWidth = 493
        end
        object panel_leave_valid_date: TPanel
          Left = 2
          Top = 83
          Width = 484
          Height = 25
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 
            'First date to start looking for restart after inactive period (s' +
            'tart of season)'
          TabOrder = 2
          ExplicitWidth = 499
          object button_start_valid_date: TRNAutoDateButton
            Left = 409
            Top = 0
            Width = 75
            Height = 25
            Align = alRight
            Caption = 'No Date'
            DoubleBuffered = True
            ParentDoubleBuffered = False
            TabOrder = 0
            ExplicitLeft = 424
          end
        end
        object panel_start_valid_date: TPanel
          Left = 2
          Top = 108
          Width = 484
          Height = 25
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'First date to start looking for inactive period (end of season)'
          TabOrder = 3
          ExplicitWidth = 499
          object button_leave_valid_date: TRNAutoDateButton
            Left = 409
            Top = 0
            Width = 75
            Height = 25
            Align = alRight
            Caption = 'No Date'
            DoubleBuffered = True
            ParentDoubleBuffered = False
            TabOrder = 0
            ExplicitLeft = 424
          end
        end
      end
      object Edit1: TEdit
        AlignWithMargins = True
        Left = 288
        Top = 15
        Width = 190
        Height = 21
        Anchors = [akLeft, akTop, akRight]
        BorderStyle = bsNone
        Color = clInfoBk
        TabOrder = 2
        Text = '<- Select one of these modes'
        ExplicitWidth = 205
      end
    end
    object groupbox_senescence: TGroupBox
      Left = 0
      Top = -1276
      Width = 492
      Height = 184
      Align = alTop
      Caption = 'Senescence'
      TabOrder = 12
      DesignSize = (
        492
        184)
      object label_senescence_perennial: TLabel
        Left = 223
        Top = 16
        Width = 258
        Height = 13
        ParentCustomHint = False
        Anchors = [akTop, akRight]
        Caption = '(note that perennials may now have leaf senescence)'
        ExplicitLeft = 230
      end
      object checkbox_senesces: TRNAutoCheckBox
        Left = 2
        Top = 15
        Width = 488
        Height = 17
        Align = alTop
        Anchors = [akTop, akRight]
        Caption = 'Senesces'
        State = cbGrayed
        TabOrder = 0
        ExplicitWidth = 503
      end
      object groupbox_LAI_duration: TGroupBox
        Left = 2
        Top = 32
        Width = 488
        Height = 65
        Align = alTop
        Caption = 'LAI duration (for LAI based canopy growth)'
        TabOrder = 1
        ExplicitWidth = 503
        object edit_leaf_duration_sensitivity_stress: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 36
          Width = 478
          Height = 21
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Leaf area duration sensitivity to water stress'
          TabOrder = 0
          ExplicitWidth = 493
        end
        object edit_deg_day_leaf_duration: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 15
          Width = 478
          Height = 21
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Leaf area duration'
          TabOrder = 1
          ExplicitWidth = 493
        end
      end
      object radiogroup_absission: TRNAutoRadioGroup
        Left = 2
        Top = 97
        Width = 488
        Height = 56
        Hint = 'What happens to biomass as it dies on the plant'
        Align = alTop
        Caption = 'Absicission'
        Columns = 3
        Items.Strings = (
          'none'
          'evergreen'
          'semi-evergreen'
          'marcescent'
          'semi-deciduous'
          'deciduous')
        ParentShowHint = False
        ShowHint = True
        TabOrder = 2
        OnClick = radiogroup_absissionClick
        ExplicitWidth = 503
      end
      object edit_linger: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 156
        Width = 482
        Height = 21
        Hint = 'remain standing/attached to'
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Time that senesced leaves linger with the plant'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 3
        ExplicitWidth = 497
      end
    end
    object groupbox_hardiness: TGroupBox
      Left = 0
      Top = -1824
      Width = 492
      Height = 113
      Align = alTop
      Caption = 'Hardiness'
      TabOrder = 13
      object checkbox_sensitive_to_cold: TRNAutoCheckBox
        Left = 2
        Top = 15
        Width = 488
        Height = 17
        Align = alTop
        Caption = 'Sensitive to cold temperatures'
        State = cbGrayed
        TabOrder = 0
        OnClick = checkbox_sensitive_to_coldClick
        ExplicitWidth = 503
      end
      object groupbox_cold_temperature_sensitivity: TGroupBox
        Left = 2
        Top = 32
        Width = 488
        Height = 81
        Align = alTop
        Caption = 'Cold temperature sensitivity'
        TabOrder = 1
        ExplicitWidth = 503
        DesignSize = (
          488
          81)
        object Label3: TLabel
          Left = 335
          Top = 0
          Width = 31
          Height = 13
          Caption = 'leaves'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlue
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object edit_damage_cold_temperature: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 15
          Width = 478
          Height = 21
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Cold temperature which begins to damage the plant'
          TabOrder = 1
          ExplicitWidth = 493
        end
        object edit_lethal_cold_temperature: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 36
          Width = 478
          Height = 21
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Cold temperature which is lethal to the plant'
          TabOrder = 2
          ExplicitWidth = 493
        end
        object edit_salvageable_days_before_maturity: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 57
          Width = 478
          Height = 21
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Number of days before maturity to salvage yield'
          TabOrder = 3
          ExplicitWidth = 493
        end
        object groupbox_hardiness_fruit: TGroupBox
          Left = 245
          Top = 0
          Width = 73
          Height = 62
          Anchors = [akTop, akRight]
          Caption = 'flower/fruit'
          TabOrder = 0
          ExplicitLeft = 260
          object edit_hardiness_fruit_damage: TRNAutoFloatEdit
            Left = 2
            Top = 15
            Width = 69
            Height = 21
            Align = alTop
            Alignment = taRightJustify
            Lines.Strings = (
              '0')
            TabOrder = 0
          end
          object edit_hardiness_fruit_lethal: TRNAutoFloatEdit
            Left = 2
            Top = 36
            Width = 69
            Height = 21
            Align = alTop
            Alignment = taRightJustify
            Lines.Strings = (
              '0')
            TabOrder = 1
          end
        end
      end
    end
    object groupbox_residue: TGroupBox
      Left = 0
      Top = -1711
      Width = 492
      Height = 242
      Align = alTop
      Caption = 'Residue'
      TabOrder = 14
      object panel_residue_1: TPanel
        Left = 2
        Top = 15
        Width = 488
        Height = 82
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        ExplicitWidth = 503
        object radiogroup_RULSE2_residue_type: TRNAutoRadioGroup
          Left = 0
          Top = 0
          Width = 187
          Height = 82
          Align = alLeft
          Caption = 'RUSLE2 residue type'
          Items.Strings = (
            'unknown (defaults to moderate)'
            'fragile/very small (I.e.soybeans)'
            'mod. tough/short (I.e.wheat)'
            'nonfragile/med. (I.e. corn)'
            'woody/large')
          TabOrder = 0
        end
        object residue_panel_1A: TPanel
          Left = 187
          Top = 0
          Width = 301
          Height = 82
          Align = alClient
          BevelOuter = bvNone
          TabOrder = 1
          ExplicitWidth = 316
          object edit_stubble_area_covered_to_mass_ratio: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 3
            Top = 21
            Width = 295
            Height = 21
            Margins.Top = 0
            Margins.Bottom = 0
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Stubble area covered to mass ratio'
            TabOrder = 0
            ExplicitWidth = 310
          end
          object edit_carbon_fraction: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 3
            Top = 0
            Width = 295
            Height = 21
            Margins.Top = 0
            Margins.Bottom = 0
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Top and root carbon fraction'
            TabOrder = 1
            ExplicitWidth = 310
          end
          object edit_surface_area_covered_to_mass_ratio: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 3
            Top = 42
            Width = 295
            Height = 21
            Margins.Top = 0
            Margins.Bottom = 0
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Flattened surface residue area covered to mass ratio'
            TabOrder = 2
            ExplicitWidth = 310
          end
          object edit_detrition_time: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 3
            Top = 63
            Width = 295
            Height = 21
            Hint = 
              'Accounts for disintigration as a result of physical processes su' +
              'ch as wind damage, abrasion, photodegradation, etc..'
            Margins.Top = 0
            Margins.Bottom = 0
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Days to 50% detrition'
            ParentShowHint = False
            ShowHint = True
            TabOrder = 3
            ExplicitWidth = 310
          end
        end
      end
      object panel_residue_2: TPanel
        Left = 2
        Top = 97
        Width = 488
        Height = 144
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 1
        ExplicitWidth = 503
        object Label1: TLabel
          Left = 4
          Top = 38
          Width = 59
          Height = 13
          Caption = 'Top biomass'
        end
        object Label4: TLabel
          Left = 4
          Top = 62
          Width = 64
          Height = 13
          Caption = 'Root biomass'
        end
        object Label14: TLabel
          Left = 172
          Top = 6
          Width = 56
          Height = 13
          Caption = 'Fast cycling'
        end
        object Label18: TLabel
          Left = 196
          Top = 22
          Width = 24
          Height = 13
          Caption = '(0-1)'
        end
        object Label15: TLabel
          Left = 244
          Top = 6
          Width = 57
          Height = 13
          Caption = 'Slow cycling'
        end
        object Label19: TLabel
          Left = 268
          Top = 22
          Width = 24
          Height = 13
          Caption = '(0-1)'
        end
        object Label16: TLabel
          Left = 307
          Top = 6
          Width = 80
          Height = 13
          Caption = 'Lignified biomass'
        end
        object Label20: TLabel
          Left = 340
          Top = 22
          Width = 24
          Height = 13
          Caption = '(0-1)'
        end
        object Label21: TLabel
          Left = 400
          Top = 22
          Width = 48
          Height = 13
          Caption = 'Checksum'
        end
        object edit_fast_cycling_top_fraction: TRNAutoFloatEdit
          Left = 168
          Top = 40
          Width = 71
          Height = 24
          Alignment = taRightJustify
          Lines.Strings = (
            '0')
          TabOrder = 0
          OnExit = update_top_biomass_checksum
        end
        object edit_slow_cycling_top_fraction: TRNAutoFloatEdit
          Left = 238
          Top = 40
          Width = 70
          Height = 24
          Alignment = taRightJustify
          Lines.Strings = (
            '0')
          TabOrder = 1
          OnExit = update_top_biomass_checksum
        end
        object edit_lignified_top_fraction: TRNAutoFloatEdit
          Left = 308
          Top = 40
          Width = 70
          Height = 24
          Alignment = taRightJustify
          Lines.Strings = (
            '0')
          TabOrder = 2
          OnExit = update_top_biomass_checksum
        end
        object top_biomass_checksum: TRNAutoFloatEdit
          Left = 392
          Top = 40
          Width = 70
          Height = 24
          Alignment = taRightJustify
          Lines.Strings = (
            '0')
          TabOrder = 3
        end
        object edit_fast_cycling_root_fraction: TRNAutoFloatEdit
          Left = 168
          Top = 64
          Width = 70
          Height = 24
          Alignment = taRightJustify
          Lines.Strings = (
            '0')
          TabOrder = 4
          OnExit = update_root_biomass_checksum
        end
        object edit_slow_cycling_root_fraction: TRNAutoFloatEdit
          Left = 238
          Top = 64
          Width = 70
          Height = 24
          Alignment = taRightJustify
          Lines.Strings = (
            '0')
          TabOrder = 5
          OnExit = update_root_biomass_checksum
        end
        object edit_lignified_root_fraction: TRNAutoFloatEdit
          Left = 308
          Top = 64
          Width = 70
          Height = 24
          Alignment = taRightJustify
          Lines.Strings = (
            '0')
          TabOrder = 6
          OnExit = update_root_biomass_checksum
        end
        object root_biomass_checksum: TRNAutoFloatEdit
          Left = 392
          Top = 64
          Width = 70
          Height = 24
          Alignment = taRightJustify
          Lines.Strings = (
            '0')
          TabOrder = 7
        end
        object panel_residue_advanced: TPanel
          Left = 0
          Top = 88
          Width = 485
          Height = 25
          BevelOuter = bvNone
          TabOrder = 8
          object Label7: TLabel
            Left = 4
            Top = 0
            Width = 153
            Height = 31
            AutoSize = False
            Caption = 'Number of days to reach 50% decomposition (days)'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clMaroon
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            WordWrap = True
          end
          object edit_fast_cycling_decomposition_time_50: TRNAutoFloatEdit
            Left = 168
            Top = 0
            Width = 70
            Height = 24
            Alignment = taRightJustify
            Lines.Strings = (
              '0')
            TabOrder = 0
          end
          object edit_slow_cycling_decomposition_time_50: TRNAutoFloatEdit
            Left = 238
            Top = 0
            Width = 70
            Height = 24
            Alignment = taRightJustify
            Lines.Strings = (
              '0')
            TabOrder = 1
          end
          object edit_lignified_decomposition_time_50: TRNAutoFloatEdit
            Left = 308
            Top = 0
            Width = 70
            Height = 24
            Alignment = taRightJustify
            Lines.Strings = (
              '0')
            TabOrder = 2
          end
        end
        object edit_fast_cycling_C_N_ratio: TRNAutoFloatEdit
          Left = 168
          Top = 118
          Width = 71
          Height = 24
          Alignment = taRightJustify
          Lines.Strings = (
            '0')
          TabOrder = 9
          Visible = False
        end
        object edit_slow_cycling_C_N_ratio: TRNAutoFloatEdit
          Left = 238
          Top = 118
          Width = 70
          Height = 24
          Alignment = taRightJustify
          Lines.Strings = (
            '0')
          TabOrder = 10
          Visible = False
        end
        object edit_lignified_C_N_ratio: TRNAutoFloatEdit
          Left = 308
          Top = 118
          Width = 70
          Height = 24
          Alignment = taRightJustify
          Lines.Strings = (
            '0')
          TabOrder = 11
          Visible = False
        end
      end
    end
    object groupbox_nitrogen: TGroupBox
      Left = 0
      Top = -2247
      Width = 492
      Height = 262
      Align = alTop
      Caption = 'Nitrogen'
      TabOrder = 15
      object groupbox_nitrogen_demand: TGroupBox
        Left = 2
        Top = 15
        Width = 488
        Height = 81
        Align = alTop
        Caption = 'Demand'
        TabOrder = 0
        ExplicitWidth = 503
        DesignSize = (
          488
          81)
        object edit_demand_adjust: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 15
          Width = 478
          Height = 21
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Nitrogen demand adjustment'
          TabOrder = 0
          ExplicitWidth = 493
        end
        object edit_N_max_stubble: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 36
          Width = 478
          Height = 21
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Maximum N concentration of chaff and stubble'
          TabOrder = 1
          ExplicitWidth = 493
        end
        object edit_root_N_conc: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 57
          Width = 478
          Height = 21
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Standard root N concentration'
          TabOrder = 2
          ExplicitWidth = 493
        end
        object button_nitrogen_fixation: TRNAutoCheckBox
          Left = 144
          Top = -2
          Width = 341
          Height = 17
          Anchors = [akLeft, akTop, akRight]
          Caption = 'Nitrogen fixation (I.e. for legumes)'
          TabOrder = 3
          ExplicitWidth = 356
        end
      end
      object groupbox_nitrogen_uptake: TGroupBox
        Left = 2
        Top = 96
        Width = 488
        Height = 104
        Align = alTop
        Caption = 'Uptake'
        TabOrder = 1
        ExplicitWidth = 503
        object edit_PAW_where_N_uptake_rate_decreases: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 78
          Width = 478
          Height = 21
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Plant available water at which N uptake starts decreasing'
          TabOrder = 0
          ExplicitWidth = 493
        end
        object edit_residual_N_not_available_for_uptake: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 36
          Width = 478
          Height = 21
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Residual N not available for uptake'
          TabOrder = 1
          ExplicitWidth = 493
        end
        object edit_N_max_daily_uptake_rate: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 15
          Width = 478
          Height = 21
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Maximum uptake during rapid linear growth'
          TabOrder = 2
          ExplicitWidth = 493
        end
        object edit_soil_N_conc_where_N_uptake_decreases: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 57
          Width = 478
          Height = 21
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Soil N concentration at which N uptake starts decreasing'
          TabOrder = 3
          ExplicitWidth = 493
        end
      end
      object radiogroup_nitrogen_leaf_stress_mode: TRNAutoRadioGroup
        Left = 2
        Top = 200
        Width = 488
        Height = 60
        Align = alClient
        Caption = 
          'Leaf expansion is reduced when canopy N concentration falls belo' +
          'w '
        Items.Strings = (
          'No effect of nitrogen stress (as prior to version 4.07.05)'
          'the critical level with full stress at the minimum level'
          
            'the midpoint between  the maximum and critical levels with full ' +
            'stress at the midpoint between the critical and minimum levels')
        TabOrder = 2
        ExplicitWidth = 503
      end
    end
    object groupbox_salinity: TGroupBox
      Left = 0
      Top = -1364
      Width = 492
      Height = 88
      Align = alTop
      Caption = 'Salinity'
      TabOrder = 16
      object Label29: TLabel
        Left = 2
        Top = 57
        Width = 488
        Height = 32
        Align = alTop
        AutoSize = False
        Caption = 
          'These parameters are optional.  They are not used unless the sal' +
          'inity simulation submodel is enabled (in the scenario model opti' +
          'ons)'
        Color = clInfoBk
        ParentColor = False
        Transparent = False
        WordWrap = True
        ExplicitWidth = 496
      end
      object edit_salt_tolerance_P: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 36
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Salinity tolerance exponent (Van-Genuchten p)'
        TabOrder = 0
        ExplicitWidth = 497
      end
      object edit_osmotic_pot_50: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 15
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Soil solution osmotic potential for 50% yield reduction'
        TabOrder = 1
        ExplicitWidth = 497
      end
    end
    object groupbox_CO2: TGroupBox
      Left = 0
      Top = -1469
      Width = 492
      Height = 105
      Align = alTop
      Caption = 'CO2'
      TabOrder = 17
      object Label28: TLabel
        Left = 2
        Top = 78
        Width = 488
        Height = 27
        Align = alTop
        AutoSize = False
        Caption = 
          'These parameters are optional.  They are not used unless the CO2' +
          ' simulation submodel is enabled (in the scenario model options)'
        Color = clInfoBk
        ParentColor = False
        Transparent = False
        WordWrap = True
        ExplicitWidth = 496
      end
      object edit_CO2_baseline_reference_conc: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 57
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Elevated to baseline growth ratio'
        TabOrder = 0
        ExplicitWidth = 497
      end
      object edit_CO2_elevated_reference_conc: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 36
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Elevated reference atmospheric CO2 concentration'
        TabOrder = 1
        ExplicitWidth = 497
      end
      object edit_CO2_growth_ratio_elevated_to_baseline: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 15
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Baseline reference atmospheric CO2 concentration'
        TabOrder = 2
        ExplicitWidth = 497
      end
    end
    object groupbox_fruit: TGroupBox
      Left = 0
      Top = -1985
      Width = 492
      Height = 161
      Align = alTop
      Caption = 'Fruit'
      TabOrder = 18
      object edit_initial_reserves_release_rate: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 78
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Initial release rate of biomass reserves (per day)'
        TabOrder = 0
        ExplicitWidth = 497
      end
      object edit_initial_fruit_mass: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 57
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Initial fruit mass'
        TabOrder = 1
        ExplicitWidth = 497
      end
      object edit_fruit_fract_total_solids: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 36
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Fraction of fruit dry matter'
        TabOrder = 2
        ExplicitWidth = 497
      end
      object edit_fruit_load_max: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 5
        Top = 15
        Width = 482
        Height = 21
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Maximum fruit load (fresh mass)'
        TabOrder = 3
        ExplicitWidth = 497
      end
      object panel_grape_or_other: TPanel
        Left = 2
        Top = 99
        Width = 488
        Height = 62
        Margins.Top = 0
        Margins.Bottom = 0
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 4
        ExplicitWidth = 503
        object groupbox_fruit_grape: TGroupBox
          Left = 2
          Top = 123
          Width = 466
          Height = 61
          Caption = 'Grape'
          TabOrder = 0
          object edit_clusters_per_vine: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 5
            Top = 15
            Width = 456
            Height = 21
            Margins.Top = 0
            Margins.Bottom = 0
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Clusters per vine'
            TabOrder = 0
          end
          object edit_berries_per_cluster: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 5
            Top = 36
            Width = 456
            Height = 21
            Margins.Top = 0
            Margins.Bottom = 0
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Berries per cluster'
            TabOrder = 1
          end
        end
        object GroupBox2: TGroupBox
          Left = 2
          Top = 123
          Width = 466
          Height = 61
          Caption = 'Grape'
          TabOrder = 1
          object RNAutoParameterEditBar1: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 5
            Top = 15
            Width = 456
            Height = 21
            Margins.Top = 0
            Margins.Bottom = 0
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Clusters per vine'
            TabOrder = 0
          end
          object RNAutoParameterEditBar3: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 5
            Top = 36
            Width = 456
            Height = 21
            Margins.Top = 0
            Margins.Bottom = 0
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Berries per cluster'
            TabOrder = 1
          end
        end
        object groupbox_grape: TGroupBox
          Left = 267
          Top = 0
          Width = 221
          Height = 62
          Align = alClient
          Caption = 'Grape'
          TabOrder = 2
          ExplicitWidth = 236
          object RNAutoParameterEditBar5: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 5
            Top = 15
            Width = 211
            Height = 21
            Margins.Top = 0
            Margins.Bottom = 0
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Clusters per vine'
            TabOrder = 0
            ExplicitWidth = 226
          end
          object RNAutoParameterEditBar6: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 5
            Top = 36
            Width = 211
            Height = 21
            Margins.Top = 0
            Margins.Bottom = 0
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Berries per cluster'
            TabOrder = 1
            ExplicitWidth = 226
          end
        end
        object groupbox_fruit_other: TGroupBox
          Left = 0
          Top = 0
          Width = 267
          Height = 62
          Align = alLeft
          Caption = 'Pome, Drupe, Hesperidium etc..'
          TabOrder = 3
          object edit_fruits_per_tree: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 5
            Top = 15
            Width = 257
            Height = 21
            Margins.Top = 0
            Margins.Bottom = 0
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Fruits per tree'
            TabOrder = 0
          end
        end
      end
    end
    object groupbox_CROPGRO: TGroupBox
      Left = 0
      Top = 37
      Width = 492
      Height = 39
      Align = alTop
      Caption = 'CROPGRO'
      TabOrder = 19
    end
    object groupbox_photoperiod: TGroupBox
      Left = 0
      Top = -2718
      Width = 492
      Height = 107
      Align = alTop
      Caption = 'Photo-period'
      TabOrder = 20
      object radiogroup_photoperiod_consideration: TRNAutoRadioGroup
        Left = 2
        Top = 15
        Width = 110
        Height = 90
        Align = alLeft
        Caption = 'Consideration'
        Items.Strings = (
          'none'
          'Short-day crop'
          'Long-day crop')
        TabOrder = 0
        OnClick = radiogroup_photoperiod_considerationClick
      end
      object groupbox_photoperiod_daylength: TGroupBox
        Left = 112
        Top = 15
        Width = 378
        Height = 90
        Align = alClient
        Caption = 'Day length affects flowering development'
        TabOrder = 1
        ExplicitWidth = 393
        object caption_at_which_stopped: TLabel
          Left = 2
          Top = 15
          Width = 374
          Height = 13
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Caption = 'day length above which'
          ExplicitWidth = 114
        end
        object caption_at_which_constrained: TLabel
          Left = 2
          Top = 49
          Width = 374
          Height = 13
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Caption = 'day length below which'
          ExplicitWidth = 112
        end
        object edit_stop_daylength: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 28
          Width = 368
          Height = 21
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'development is stopped'
          TabOrder = 0
          ExplicitWidth = 383
        end
        object edit_constrained_daylength: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 5
          Top = 62
          Width = 368
          Height = 21
          Margins.Top = 0
          Margins.Bottom = 0
          Align = alTop
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'development is not constrained'
          TabOrder = 1
          ExplicitWidth = 383
        end
      end
    end
    object radiogroup_emergence_model: TRNAutoRadioGroup
      Left = 0
      Top = -490
      Width = 492
      Height = 34
      Align = alTop
      Caption = 'Emergence submodel'
      Columns = 2
      Items.Strings = (
        'Thermal time'
        'Hydrothermal time')
      TabOrder = 21
      OnClick = radiogroup_emergence_modelClick
    end
  end
  object groupbox_jumpto: TAdvGroupBox
    Left = 0
    Top = 0
    Width = 177
    Height = 595
    Align = alLeft
    Caption = 'Show/Jump to'
    TabOrder = 1
    object scrollbox_jumpto: TScrollBox
      Left = 2
      Top = 16
      Width = 173
      Height = 577
      Align = alClient
      BevelInner = bvNone
      BevelOuter = bvNone
      BorderStyle = bsNone
      TabOrder = 0
      ExplicitLeft = 0
      ExplicitTop = 22
      ExplicitWidth = 185
      ExplicitHeight = 561
      object radiogroup_crop_model: TRNAutoRadioGroup
        Left = 0
        Top = 0
        Width = 156
        Height = 71
        Align = alTop
        Caption = 'Crop model'
        Items.Strings = (
          'CropSyst generalized crops (grain, root, and leaf)'
          
            'CropSyst orchard/vineyard fruit model (fruit trees, stone fruit,' +
            ' grapes)'
          'CROPGRO (Peas, beans, soy, legumes) (not implemented)')
        TabOrder = 0
        OnClick = radiogroup_crop_modelClick
        ExplicitWidth = 171
      end
      object checklistbox_view_panels: TRNAutoBitCheckListBox
        Left = 0
        Top = 71
        Width = 156
        Height = 290
        OnClickCheck = checklistbox_view_panelsClickCheck
        Align = alTop
        ItemHeight = 13
        Items.Strings = (
          'Defaults'
          'Classification'
          'Thermal time accumulation'
          'Transpiration'
          'Vernalization'
          'Photo-period'
          'Emergence'
          'Phenology'
          'Canopy growth'
          'Attainable growth'
          'Senescence'
          'Dormacy/Seasonal'
          'Root'
          'Fruit'
          'Layout'
          'Harvest'
          'Hardiness'
          'Residue'
          'Nitrogen'
          'Salinity'
          'CO2'
          'CROPGRO')
        TabOrder = 1
        OnClick = checklistbox_view_panelsClick
        ExplicitWidth = 171
      end
      object groupbox_defaults: TGroupBox
        Left = 0
        Top = 361
        Width = 156
        Height = 270
        Align = alTop
        Caption = 'Defaults'
        TabOrder = 2
        ExplicitWidth = 171
        object Label2: TLabel
          Left = 1
          Top = 61
          Width = 154
          Height = 60
          Align = alTop
          AutoSize = False
          Caption = 
            'To load default values, select the crop type.  All current param' +
            'eter settings will be updated.'
          Color = clInfoBk
          ParentColor = False
          WordWrap = True
          ExplicitWidth = 156
        end
        object Label24: TLabel
          Left = 1
          Top = 14
          Width = 154
          Height = 26
          Align = alTop
          AutoSize = False
          Caption = 'Default crop parameters are available for some crop types.'
          Color = clInfoBk
          ParentColor = False
          WordWrap = True
          ExplicitLeft = 8
          ExplicitTop = 15
          ExplicitWidth = 550
        end
        object Label25: TLabel
          Left = 1
          Top = 146
          Width = 154
          Height = 67
          Align = alTop
          AutoSize = False
          Caption = 
            'This button will launch the crop calibration utility to calibrat' +
            'e parameters for  location/cultivar. First select the default cr' +
            'op type above.  Note that crop calibration is currently only ava' +
            'ilable for annual crops.'
          Color = clInfoBk
          ParentColor = False
          WordWrap = True
          ExplicitWidth = 156
        end
        object crop_class_combobox: TComboBox
          Left = 1
          Top = 40
          Width = 154
          Height = 21
          Align = alTop
          TabOrder = 0
          Text = '<default crop not currently selected>'
          ExplicitWidth = 166
        end
        object button_calibrate: TButton
          Left = 1
          Top = 121
          Width = 154
          Height = 25
          Hint = 'This will open'
          Align = alTop
          Caption = 'Calibrate crop parameters'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          ParentShowHint = False
          ShowHint = True
          TabOrder = 1
          Visible = False
          OnClick = button_calibrateClick
          ExplicitWidth = 166
        end
      end
    end
  end
end
