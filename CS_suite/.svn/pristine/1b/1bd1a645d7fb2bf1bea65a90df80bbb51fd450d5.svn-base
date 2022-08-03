object Irrigation_application_form: TIrrigation_application_form
  Left = 37
  Top = -890
  Width = 516
  Height = 300
  Align = alClient
  Caption = 'Irrigation application'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDefaultPosOnly
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 508
    Height = 266
    ActivePage = tabsheet_application_conditions
    Align = alClient
    TabOrder = 0
    object tabsheet_application_conditions: TTabSheet
      Caption = 'Application conditions'
      object Label3: TLabel
        Left = 0
        Top = 212
        Width = 500
        Height = 26
        Align = alBottom
        AutoSize = False
        Caption = 
          'Application conditions only apply to automatic irrigation or per' +
          'iodic specified events'
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
      end
      object panel_consideration_mode: TPanel
        Left = 0
        Top = 0
        Width = 500
        Height = 50
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        object Label2: TLabel
          Left = 185
          Top = 0
          Width = 315
          Height = 50
          Align = alClient
          AutoSize = False
          Caption = 
            'Typically '#39'Soil water depletion'#39' mode is used. Leaf water potent' +
            'ial mode is intended for fruit orchard/vineyard.'
          Color = clInfoBk
          ParentColor = False
          WordWrap = True
        end
        object radiogroup_consideration: TAutoRadioGroup
          Left = 0
          Top = 0
          Width = 185
          Height = 50
          Align = alLeft
          Caption = 'Consideration mode'
          Items.Strings = (
            'Soil water depletion'
            'Leaf water potential')
          TabOrder = 0
          OnClick = radiogroup_considerationClick
        end
      end
      object groupbox_depletion_constraints: TGroupBox
        Left = 0
        Top = 71
        Width = 500
        Height = 136
        Align = alTop
        Caption = 'Depletion constraints'
        TabOrder = 2
        object max_allowable_depletion_editbar: TAutoFloat32EditBar
          Left = 2
          Top = 15
          Width = 496
          Height = 22
          Align = alTop
          AutoScroll = False
          TabOrder = 0
          Description_label = 'Maximum allowable depletion'
          Units_label = '0-1'
        end
        object depletion_obs_fract_root_depth_edit: TAutoFloat32EditBar
          Left = 2
          Top = 111
          Width = 496
          Height = 22
          Hint = 
            'Usually use a value 1 or less. Greater than 1 will evaluate deep' +
            'er than the roots.'
          Align = alTop
          AutoScroll = False
          ParentShowHint = False
          ShowHint = True
          TabOrder = 2
          Description_label = 'Fraction of current root depth'
          Units_label = '0 to 2'
        end
        object depletion_observe_depth_editbar: TAutoFloat32EditBar
          Tag = 1
          Left = 2
          Top = 89
          Width = 496
          Height = 22
          Align = alTop
          AutoScroll = False
          TabOrder = 1
          Description_label = 'Depletion observation depth'
          Units_label = 'm'
        end
        object panel_observation_depth_model: TPanel
          Left = 2
          Top = 37
          Width = 496
          Height = 52
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 3
          object depletion_contigency_note: TLabel
            Left = 401
            Top = 0
            Width = 95
            Height = 52
            Align = alClient
            AutoSize = False
            Caption = 
              'These options can be set because this event has postponable cont' +
              'igency.'
            Color = clInfoBk
            ParentColor = False
            WordWrap = True
          end
          object radiobutton_depletion_observation_depth_mode: TAutoRadioGroup
            Left = 0
            Top = 0
            Width = 401
            Height = 52
            Align = alLeft
            Caption = 'Observation depth mode'
            Columns = 2
            Items.Strings = (
              'at a constant fixed depth'
              'at a fraction of the current root depth'
              'the entire profile')
            TabOrder = 0
            OnClick = radiobutton_depletion_observation_depth_modeClick
          end
        end
      end
      object editbar_leaf_water_potential: TAutoFloat32EditBar
        Left = 0
        Top = 50
        Width = 500
        Height = 21
        Hint = 
          'Irrigation will occur when the leaf water potential becomes more' +
          ' negative than this value.'
        Align = alTop
        AutoScroll = False
        TabOrder = 1
        Description_label = 'Leaf water potential'
        Units_label = '-J/kg'
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Application amount'
      ImageIndex = 1
      object panel_application_mode: TPanel
        Left = 0
        Top = 0
        Width = 500
        Height = 51
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        object depletion_constraints_note: TLabel
          Left = 185
          Top = 0
          Width = 315
          Height = 51
          Align = alClient
          AutoSize = False
          Caption = 
            'If this operation is schedule to repeat, the "Irrigate to a spec' +
            'ified refill point" (based on soil conditions) may be useful.  I' +
            'f this is a single event, simply use "Irrigate a fixed amount".'
          Color = clInfoBk
          ParentColor = False
          WordWrap = True
        end
        object application_mode_radiogroup: TAutoRadioGroup
          Left = 0
          Top = 0
          Width = 185
          Height = 51
          Align = alLeft
          Caption = 'Application mode'
          Items.Strings = (
            'Irrigate a fixed amount'
            'Irrigate to a specified refill point')
          TabOrder = 0
          OnClick = application_mode_radiogroup_onclick
        end
      end
      object amount_editbar: TAutoFloat32EditBar
        Left = 0
        Top = 51
        Width = 500
        Height = 22
        Hint = 
          'Enter 0.0 to supply enough water to refill to plant available wa' +
          'ter'
        Align = alTop
        AutoScroll = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        Description_label = 'Total irrigation'
        Units_label = 'mm'
      end
      object panel_refill: TPanel
        Left = 0
        Top = 73
        Width = 500
        Height = 90
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 2
        object net_irrigation_mult_editbar: TAutoFloat32EditBar
          Left = 0
          Top = 22
          Width = 500
          Height = 22
          Hint = 
            'This parameter is used to add a little more irrigation to compen' +
            'sate for inefficiency.  (Values > 1.0 are less efficient)'
          Align = alTop
          AutoScroll = False
          ParentShowHint = False
          ShowHint = True
          TabOrder = 1
          Description_label = 'Net irrigation multiplier (1.0 is 100% efficient)'
          Units_label = '(-)'
        end
        object max_application_editbar: TAutoFloat32EditBar
          Left = 0
          Top = 44
          Width = 500
          Height = 22
          Hint = 
            'This can be used to fix an upper limit a recharging option is sp' +
            'ecified (Enter 0.0 if no maximum is applied)'
          Align = alTop
          AutoScroll = False
          ParentShowHint = False
          ShowHint = True
          TabOrder = 2
          Description_label = 'Irrigation system maximum application capacity'
          Units_label = 'mm'
        end
        object min_application_editbar: TAutoFloat32EditBar
          Left = 0
          Top = 66
          Width = 500
          Height = 22
          Hint = 
            'This can be used to specify the minimum amount of water the irri' +
            'gation system can deliver (Enter 0.0 if no maximum is applied)'
          Align = alTop
          AutoScroll = False
          ParentShowHint = False
          ShowHint = True
          TabOrder = 3
          Description_label = 'Irrigation system minimum application capability'
          Units_label = 'mm'
        end
        object refill_point_edit_bar: TAutoFloat32EditBar
          Left = 0
          Top = 0
          Width = 500
          Height = 22
          Hint = 
            'This is the fraction of plant available water to refill to (0=pe' +
            'rmanent wilt point, 1=field capacity)'
          Align = alTop
          AutoScroll = False
          ParentShowHint = False
          ShowHint = True
          TabOrder = 0
          Description_label = 'Refill point'
          Units_label = '(0-1)'
        end
      end
      object GroupBox1: TGroupBox
        Left = 0
        Top = 163
        Width = 500
        Height = 72
        Align = alTop
        Caption = 'Soil fraction wetted by irrigation'
        TabOrder = 3
        object edit_irrig_wetted_soil_volume: TAutoFloat32EditBar
          Left = 2
          Top = 37
          Width = 496
          Height = 22
          Align = alTop
          AutoScroll = False
          ParentShowHint = False
          ShowHint = True
          TabOrder = 1
          Description_label = 'Soil profile volume'
          Units_label = '(0-1)'
        end
        object edit_irrig_wetted_surface_evap: TAutoFloat32EditBar
          Left = 2
          Top = 15
          Width = 496
          Height = 22
          Align = alTop
          AutoScroll = False
          ParentShowHint = False
          ShowHint = True
          TabOrder = 0
          Description_label = 'Soil surface subject to soil evaporation'
          Units_label = '(0-1)'
        end
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Solute concentrations'
      ImageIndex = 2
      object Label1: TLabel
        Left = 0
        Top = 225
        Width = 500
        Height = 13
        Align = alBottom
        AutoSize = False
        Caption = 'Enter 0 values for concentration if not applicable.'
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
      end
      object salinity_editbar: TAutoFloat32EditBar
        Left = 0
        Top = 0
        Width = 500
        Height = 22
        Align = alTop
        AutoScroll = False
        TabOrder = 0
        Description_label = 'Salt concentration (Salinity)'
        Units_label = 'dS/m'
      end
      object edit_NO3_N_conc: TAutoFloat32EditBar
        Left = 0
        Top = 22
        Width = 500
        Height = 22
        Align = alTop
        AutoScroll = False
        TabOrder = 1
        Description_label = 'Nitrate NO3 nitrogen concentration'
        Units_label = 'kg N/m³ water'
      end
      object edit_NH4_N_conc: TAutoFloat32EditBar
        Left = 0
        Top = 44
        Width = 500
        Height = 22
        Align = alTop
        AutoScroll = False
        TabOrder = 2
        Description_label = 'Ammonium NH4 nitrogen concentration'
        Units_label = 'kg N/m³ water'
      end
    end
  end
end
