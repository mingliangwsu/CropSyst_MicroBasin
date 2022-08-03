object clipping_form: Tclipping_form
  Left = 1315
  Top = 104
  Align = alClient
  Caption = 'Harvest/Clipping'
  ClientHeight = 412
  ClientWidth = 557
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object harvest_clipping_pagecontrol: TPageControl
    Left = 0
    Top = 0
    Width = 557
    Height = 412
    ActivePage = removal_mode_tabsheet
    Align = alClient
    TabOrder = 0
    OnChange = show_hide_controls
    object removal_mode_tabsheet: TTabSheet
      Caption = 'Biomass removal mode and constraints'
      DesignSize = (
        549
        384)
      object retain_GAI_mode_note: TLabel
        Left = 8
        Top = 240
        Width = 527
        Height = 41
        Anchors = [akLeft, akTop, akRight]
        AutoSize = False
        Caption = 
          'With this mode, all the removed amount is divided into the speci' +
          'fied biomatter fate pools and any remainder (biomass associated ' +
          'with the GAI retained) is left as standing biomatter (dead resid' +
          'ue if terminate crop is enabled).'
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
      end
      object remove_percentage_note: TLabel
        Left = 0
        Top = 343
        Width = 549
        Height = 41
        Align = alBottom
        AutoSize = False
        Caption = 
          'With this mode, the current above ground biomass is divied up ac' +
          'cording to the biomass fate percentages.  The amount removed for' +
          ' beneficial use is considered the yield of the clipping event.'
        Color = clInfoBk
        ParentColor = False
        WordWrap = True
        ExplicitLeft = 3
      end
      object harvest_amount_mode_radiogroup: TRNAutoRadioGroup
        Left = 0
        Top = 24
        Width = 549
        Height = 57
        Hint = 
          'When you change the biomass removal mode you need to make sure b' +
          'iomass fate sums to 100%'
        Align = alTop
        Caption = 'Mode selection'
        Items.Strings = (
          
            'Single harvest event with primary yield  based harvest index, or' +
            ' harvestable biomatter such as fruits'
          'Remove fixed amout of biomass (suitable for clipping, grazing).'
          'Remove biomass based on percentages')
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        OnClick = harvest_amount_mode_radiogroup_onclick
      end
      object remove_fixed_amount_groupbox: TGroupBox
        Left = 0
        Top = 81
        Width = 549
        Height = 145
        Align = alTop
        Caption = 'Removed fixed amount of biomass'
        TabOrder = 1
        DesignSize = (
          549
          145)
        object Label10: TLabel
          Left = 8
          Top = 86
          Width = 342
          Height = 43
          Anchors = [akLeft, akTop, akRight]
          AutoSize = False
          Caption = 
            'When a fixed amount is removed, all the  removed amount is divid' +
            'ed into the specified biomass fate pools and any remainder (rese' +
            'rve) is left as standing biomass (dead residue if terminate crop' +
            ' is enabled).'
          Color = clInfoBk
          ParentColor = False
          WordWrap = True
        end
        object remove_fixed_amount_edit: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 34
          Top = 18
          Width = 499
          Height = 22
          Hint = 'This is the fixed amount of material to remove'
          Alignment = taLeftJustify
          Anchors = [akLeft, akTop, akRight]
          BevelOuter = bvNone
          Caption = 'Fixed amount to remove'
          ParentShowHint = False
          ShowHint = True
          TabOrder = 0
        end
        object reserve_biomass_editbar: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 34
          Top = 60
          Width = 499
          Height = 21
          Hint = 
            'Primarily for grazing operations, this is used to indicate that ' +
            'some biomass cannot or should not be removed.'
          Alignment = taLeftJustify
          Anchors = [akLeft, akTop, akRight]
          BevelOuter = bvNone
          Caption = 'Reserve biomass (unavailable for clipping/grazing)'
          ParentShowHint = False
          ShowHint = True
          TabOrder = 1
        end
        object accept_less_checkbox: TRNAutoCheckBox
          Left = 80
          Top = 42
          Width = 455
          Height = 17
          Hint = 
            'If this box is not check, the operation will fail and not be per' +
            'formed if there is insufficient biomass.'
          Anchors = [akLeft, akTop, akRight]
          Caption = 
            'Accept a lesser amount of biomass removed if there is enough bio' +
            'mass to meet the reserve'
          ParentShowHint = False
          ShowHint = True
          TabOrder = 2
        end
        object goto_biomass_fate_button: TBitBtn
          Left = 365
          Top = 96
          Width = 161
          Height = 25
          Anchors = [akTop, akRight]
          Caption = 'Biomass fate must be set'
          Glyph.Data = {
            76010000424D7601000000000000760000002800000020000000100000000100
            04000000000000010000120B0000120B00001000000000000000000000000000
            800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
            33333FF3333333333333447333333333333377FFF33333333333744473333333
            333337773FF3333333333444447333333333373F773FF3333333334444447333
            33333373F3773FF3333333744444447333333337F333773FF333333444444444
            733333373F3333773FF333334444444444733FFF7FFFFFFF77FF999999999999
            999977777777777733773333CCCCCCCCCC3333337333333F7733333CCCCCCCCC
            33333337F3333F773333333CCCCCCC3333333337333F7733333333CCCCCC3333
            333333733F77333333333CCCCC333333333337FF7733333333333CCC33333333
            33333777333333333333CC333333333333337733333333333333}
          NumGlyphs = 2
          TabOrder = 3
          OnClick = goto_biomass_fate_button_onclick
        end
      end
      object GAI_groupbox: TGroupBox
        Left = 0
        Top = 226
        Width = 549
        Height = 111
        Hint = 
          'These parameters ensure that the green area index is consistent ' +
          'with the biomass removed.'
        Align = alTop
        Caption = 'Green area index'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 2
        object notea: TLabel
          Left = 8
          Top = 75
          Width = 545
          Height = 25
          AutoSize = False
          Caption = 
            'This parameter ensures that sufficient green area index is maint' +
            'ained for regrowth when the biomass is removed. Actual biomass r' +
            'emoval may be limited to presure the GAI.'
          Color = clInfoBk
          ParentColor = False
          WordWrap = True
        end
        object min_retain_GAI_edit: TRNAutoParameterEditBar
          AlignWithMargins = True
          Left = 8
          Top = 56
          Width = 539
          Height = 21
          Hint = 
            'This value insures that a minimal amount of GAI is retained in t' +
            'he field, this is to prevent the operation from removing so much' +
            ' green foliage that the crop is unable to recover.  (This may li' +
            'mit biomass removal)'
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Caption = 'Minimum GAI to be retained'
          ParentShowHint = False
          ShowHint = True
          TabOrder = 0
        end
      end
      object panel_NRCS_field_op: TPanel
        Left = 0
        Top = 0
        Width = 549
        Height = 24
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'NRCS field operation'
        TabOrder = 3
        DesignSize = (
          549
          24)
        object SpeedButton1: TSpeedButton
          Left = 522
          Top = 1
          Width = 21
          Height = 21
          Anchors = [akTop, akRight]
          Glyph.Data = {
            76010000424D7601000000000000760000002800000020000000100000000100
            04000000000000010000120B0000120B00001000000000000000000000000000
            800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
            3333333333FFFFF3333333333F797F3333333333F737373FF333333BFB999BFB
            33333337737773773F3333BFBF797FBFB33333733337333373F33BFBFBFBFBFB
            FB3337F33333F33337F33FBFBFB9BFBFBF3337333337F333373FFBFBFBF97BFB
            FBF37F333337FF33337FBFBFBFB99FBFBFB37F3333377FF3337FFBFBFBFB99FB
            FBF37F33333377FF337FBFBF77BF799FBFB37F333FF3377F337FFBFB99FB799B
            FBF373F377F3377F33733FBF997F799FBF3337F377FFF77337F33BFBF99999FB
            FB33373F37777733373333BFBF999FBFB3333373FF77733F7333333BFBFBFBFB
            3333333773FFFF77333333333FBFBF3333333333377777333333}
          NumGlyphs = 2
          OnClick = button_NRCS_helpClick
        end
        object NRCS_harvest_field_op_number_combbox: TComboBox
          Left = 112
          Top = 2
          Width = 412
          Height = 21
          Hint = 'Used for surface residue disturbance and fate'
          Anchors = [akLeft, akTop, akRight]
          ParentShowHint = False
          ShowHint = True
          TabOrder = 0
          Text = '(selection is optional but recommended)'
          OnChange = NRCS_harvest_field_op_number_combboxChange
          Items.Strings = (
            '(unknown - not listed here)'
            'Mower, swather, windrower'
            'Pruning'
            'Harvest, banana'
            'Harvest, banana remove stem'
            'Harvest, broccoli and cauliflower'
            'Harvest, cabbage and head lettuce'
            'Harvest, corn silage with cover crop'
            'Harvest, cotton'
            'Harvest, cotton and shred'
            'Harvest, cut flowers'
            'Harvest, forage sorghum'
            'Harvest, grain, grow cover'
            'Harvest, grass or legume seed, leave forage'
            'Harvest, grass seed, remove forage'
            'Harvest, hand pick'
            'Harvest, hand pull'
            'Harvest, hay, grass'
            'Harvest, hay, legume'
            'Harvest, hay, no regrowth'
            'Harvest, kenaf'
            'Harvest, killing crop'
            'Harvest, leafy veg.'
            'Harvest, legume seed, remove forage'
            'Harvest, peanut digger'
            'Harvest, plantains'
            'Harvest, root crops, digger'
            'Harvest, rootcrops, manually'
            'Harvest, silage'
            'Harvest, snapper header'
            'Harvest, stripper header'
            'Harvest, sugarcane, after burning'
            'Harvest, sugarcane, modern'
            'Harvest, sugarcane, old type'
            'Harvest, tobacco, burley'
            'Harvest, tobacco, flue cured'
            'Graze, continuous'
            'Graze, intensive rotational'
            'Graze, rotational'
            'Graze, stubble or residue')
        end
      end
    end
    object biomass_fate_tabsheet: TTabSheet
      Caption = 'Biomass fate'
      ImageIndex = 1
      DesignSize = (
        549
        384)
      object harvest_mode_page_control: TPageControl
        Left = 0
        Top = 0
        Width = 549
        Height = 227
        Hint = 
          'Select one of these biomass fate modes. The parameters specific ' +
          'to the mode will be displayed.'
        ActivePage = primary_yield_tabsheet
        Align = alClient
        ParentShowHint = False
        ShowHint = True
        Style = tsButtons
        TabOrder = 0
        OnChange = harvest_mode_onchange
        object primary_yield_tabsheet: TTabSheet
          Caption = 'Grain, tuber, leaf, fruit or root yield'
          DesignSize = (
            541
            196)
          object Label2: TLabel
            Left = 0
            Top = 0
            Width = 541
            Height = 33
            Align = alTop
            AutoSize = False
            Caption = 
              'For crop where the yield biomass is grain, fruit, flower or leaf' +
              ' head, roots or tubers; crop parameters specify the primary harv' +
              'ested biomatter based on harvest index or the accumulation of th' +
              'e yield biomass. '
            Color = clInfoBk
            ParentColor = False
            WordWrap = True
          end
          object Label1: TLabel
            Left = 0
            Top = 58
            Width = 541
            Height = 41
            Align = alTop
            AutoSize = False
            Caption = 
              'Remaining biomass (excluding yield) will be disposed as specifie' +
              'd below.  If the crop does not have harvest index or no availabl' +
              'e yield, all above ground biomass is disposed thusly.  For most ' +
              'crops, enable "Terminate crop".'
            Color = clInfoBk
            ParentColor = False
            WordWrap = True
          end
          object Label14: TLabel
            Left = 0
            Top = 33
            Width = 541
            Height = 25
            Align = alTop
            AutoSize = False
            Caption = 
              'This harvest mode is intended for such crops and is usually sche' +
              'duled to harvest when the crop reachs physiological maturity. '
            Color = clInfoBk
            ParentColor = False
            WordWrap = True
          end
          object Label15: TLabel
            Left = 0
            Top = 183
            Width = 541
            Height = 13
            Align = alBottom
            Caption = 'Of the biomass that is not primary yield, the remaining '
            ExplicitWidth = 251
          end
          object suggested_harvest_button: TBitBtn
            Left = 362
            Top = 124
            Width = 177
            Height = 25
            Anchors = [akTop, akRight]
            Caption = 'Enter suggested values'
            Glyph.Data = {
              76010000424D7601000000000000760000002800000020000000100000000100
              04000000000000010000120B0000120B00001000000000000000000000000000
              800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
              FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333393333
              333333333337F3333333333333397333333333333337FF333333333333C94333
              3333333333737F333333333333C9473333333333337373F3333333333CC94433
              3333333337F7F7F3333333333CC94473333333333737F73F33333333CCC94443
              333333337F37F37F33333333CCC94447333333337337F373F333333CCCC94444
              33333337F337F337F333333CCCC94444733333373337F3373F3333CCCCC94444
              4333337F3337FF337F3333CCCCC94444473333733F7773FF73F33CCCCC393444
              443337F37737F773F7F33CCC33393374447337F73337F33737FFCCC333393333
              444377733337F333777FC3333339333337437333333733333373}
            NumGlyphs = 2
            TabOrder = 0
            OnClick = suggested_harvest_buttonClick
          end
        end
        object clipping_tabsheet: TTabSheet
          Caption = 'Clipping'
          ImageIndex = 1
          DesignSize = (
            541
            196)
          object Label3: TLabel
            Left = 0
            Top = 0
            Width = 541
            Height = 17
            Align = alTop
            AutoSize = False
            Caption = 
              'This option is used primarily for crops where there may be multi' +
              'ple clipping events during the growing season.'
            Color = clInfoBk
            ParentColor = False
            WordWrap = True
          end
          object Label5: TLabel
            Left = 0
            Top = 67
            Width = 541
            Height = 33
            Align = alTop
            AutoSize = False
            Caption = 
              'Reminder: You can schedule clipping as a repeated event if it is' +
              ' to occur at fixed intervals, or add multiple clipping events to' +
              ' the schedule.  This mode is usually not used to terminate the c' +
              'rop.'
            Color = clInfoBk
            ParentColor = False
            WordWrap = True
          end
          object Label12: TLabel
            Left = 0
            Top = 50
            Width = 541
            Height = 17
            Align = alTop
            AutoSize = False
            Caption = 
              ' In this case all biomass is removed as specified below overridi' +
              'ng any harvest index or other crop harvest parameters.'
            Color = clInfoBk
            ParentColor = False
            WordWrap = True
          end
          object Label13: TLabel
            Left = 0
            Top = 17
            Width = 541
            Height = 33
            Align = alTop
            AutoSize = False
            Caption = 
              'This mode can be used with crops that are normally harvested for' +
              ' primary yield, but are are sometimes harvested prior to physiol' +
              'ogical maturity for fodder, silage or other uses. '
            Color = clInfoBk
            ParentColor = False
            WordWrap = True
          end
          object clipping_fate_label: TLabel
            Left = 0
            Top = 183
            Width = 541
            Height = 13
            Align = alBottom
            Caption = 'All of the clipped (actually removed from the plant)'
            ExplicitWidth = 234
          end
          object suggest_clipping_button: TBitBtn
            Left = 362
            Top = 124
            Width = 177
            Height = 25
            Anchors = [akTop, akRight]
            Caption = 'Enter suggested values'
            Glyph.Data = {
              76010000424D7601000000000000760000002800000020000000100000000100
              04000000000000010000120B0000120B00001000000000000000000000000000
              800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
              FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333393333
              333333333337F3333333333333397333333333333337FF333333333333C94333
              3333333333737F333333333333C9473333333333337373F3333333333CC94433
              3333333337F7F7F3333333333CC94473333333333737F73F33333333CCC94443
              333333337F37F37F33333333CCC94447333333337337F373F333333CCCC94444
              33333337F337F337F333333CCCC94444733333373337F3373F3333CCCCC94444
              4333337F3337FF337F3333CCCCC94444473333733F7773FF73F33CCCCC393444
              443337F37737F773F7F33CCC33393374447337F73337F33737FFCCC333393333
              444377733337F333777FC3333339333337437333333733333373}
            NumGlyphs = 2
            TabOrder = 0
            OnClick = suggest_clipping_buttonClick
          end
        end
        object last_clipping_tabsheet: TTabSheet
          Caption = 'Last clipping'
          ImageIndex = 2
          DesignSize = (
            541
            196)
          object Label4: TLabel
            Left = 0
            Top = 0
            Width = 541
            Height = 49
            Align = alTop
            AutoSize = False
            Caption = 
              'This option is used for crops with multiple other clipping event' +
              's.  One last clipping will be attempted on the scheduled date, h' +
              'arvest will occur only if there is sufficient biomass and the cr' +
              'op has not already entered dormancy.'
            Color = clInfoBk
            ParentColor = False
            WordWrap = True
          end
          object Label6: TLabel
            Left = 0
            Top = 49
            Width = 541
            Height = 49
            Align = alTop
            AutoSize = False
            Caption = 
              'Normally, with this mode, the crop will continue into dormancy a' +
              'nd restart in the spring.  Some times it may be appropriate to a' +
              'lso terminate the crop at this time  (I.e. to kill a perennial).' +
              '  In this case enable "Terminate crop".'
            Color = clInfoBk
            ParentColor = False
            WordWrap = True
          end
          object last_clipping_fate_label: TLabel
            Left = 0
            Top = 183
            Width = 541
            Height = 13
            Align = alBottom
            Caption = 'All of the clipped (actually removed from the plant)'
            ExplicitWidth = 234
          end
          object suggest_last_clipping_button: TBitBtn
            Left = 362
            Top = 170
            Width = 177
            Height = 25
            Anchors = [akRight, akBottom]
            Caption = 'Enter suggested values'
            Glyph.Data = {
              76010000424D7601000000000000760000002800000020000000100000000100
              04000000000000010000120B0000120B00001000000000000000000000000000
              800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
              FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333393333
              333333333337F3333333333333397333333333333337FF333333333333C94333
              3333333333737F333333333333C9473333333333337373F3333333333CC94433
              3333333337F7F7F3333333333CC94473333333333737F73F33333333CCC94443
              333333337F37F37F33333333CCC94447333333337337F373F333333CCCC94444
              33333337F337F337F333333CCCC94444733333373337F3373F3333CCCCC94444
              4333337F3337FF337F3333CCCCC94444473333733F7773FF73F33CCCCC393444
              443337F37737F773F7F33CCC33393374447337F73337F33737FFCCC333393333
              444377733337F333777FC3333339333337437333333733333373}
            NumGlyphs = 2
            TabOrder = 0
            OnClick = suggest_last_clipping_buttonClick
          end
        end
        object grazing_tabsheet: TTabSheet
          Caption = 'Grazing'
          ImageIndex = 3
          DesignSize = (
            541
            196)
          object Label7: TLabel
            Left = 0
            Top = 0
            Width = 541
            Height = 17
            Align = alTop
            AutoSize = False
            Caption = 
              'This option is used for forage crops.  It activates the grazing ' +
              'submodel. '
            Color = clInfoBk
            ParentColor = False
            WordWrap = True
          end
          object Label18: TLabel
            Left = 0
            Top = 183
            Width = 541
            Height = 13
            Align = alBottom
            Caption = 'Including the percent biomass grazed specified above,'
            ExplicitWidth = 257
          end
          object Label20: TLabel
            Left = 361
            Top = 58
            Width = 180
            Height = 110
            Anchors = [akTop, akRight, akBottom]
            AutoSize = False
            Caption = 
              'The grazed amount will be applied to the soil surface as an orga' +
              'nic fertilizer application. (harvest index will not be applied e' +
              'ven if the crop has harvest index parameters).'
            Color = clInfoBk
            ParentColor = False
            WordWrap = True
            ExplicitHeight = 69
          end
          object remove_for_grazing_edit: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 0
            Top = 16
            Width = 529
            Height = 22
            Alignment = taLeftJustify
            Anchors = [akLeft, akTop, akRight]
            BevelOuter = bvNone
            Caption = 'Consumed by animals'
            TabOrder = 0
            OnExit = update_total_percent
          end
          object grazing_groupbox: TGroupBox
            Left = 32
            Top = 58
            Width = 329
            Height = 64
            Anchors = [akLeft, akTop, akRight]
            Caption = 'Percent Nitrogen in produced manure (These must sum to 100%)'
            TabOrder = 2
            DesignSize = (
              329
              64)
            object grazing_OM_editbar: TRNAutoParameterEditBar
              AlignWithMargins = True
              Left = 8
              Top = 16
              Width = 313
              Height = 22
              Alignment = taLeftJustify
              Anchors = [akLeft, akTop, akRight]
              BevelOuter = bvNone
              Caption = 'from organic matter'
              TabOrder = 0
              OnExit = grazing_OM_editbar_onexit
            end
            object grazing_NH3_editbar: TRNAutoParameterEditBar
              AlignWithMargins = True
              Left = 8
              Top = 38
              Width = 313
              Height = 22
              Alignment = taLeftJustify
              Anchors = [akLeft, akTop, akRight]
              BevelOuter = bvNone
              Caption = 'from ammonia (NH3)'
              TabOrder = 1
              OnExit = grazing_NH3_editbar_onexit
            end
          end
          object biomass_returned_as_manure_editbar: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 16
            Top = 36
            Width = 513
            Height = 22
            Hint = 
              'The portion of manure production actually deposited to the field' +
              ' (the remainder is loss)'
            Alignment = taLeftJustify
            Anchors = [akLeft, akTop, akRight]
            BevelOuter = bvNone
            Caption = 'Consumed biomass returned to the field as manure'
            ParentShowHint = False
            ShowHint = True
            TabOrder = 1
          end
          object suggest_grazing_button: TBitBtn
            Left = 362
            Top = 170
            Width = 177
            Height = 25
            Anchors = [akRight, akBottom]
            Caption = 'Enter suggested values'
            Glyph.Data = {
              76010000424D7601000000000000760000002800000020000000100000000100
              04000000000000010000120B0000120B00001000000000000000000000000000
              800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
              FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333393333
              333333333337F3333333333333397333333333333337FF333333333333C94333
              3333333333737F333333333333C9473333333333337373F3333333333CC94433
              3333333337F7F7F3333333333CC94473333333333737F73F33333333CCC94443
              333333337F37F37F33333333CCC94447333333337337F373F333333CCCC94444
              33333337F337F337F333333CCCC94444733333373337F3373F3333CCCCC94444
              4333337F3337FF337F3333CCCCC94444473333733F7773FF73F33CCCCC393444
              443337F37737F773F7F33CCC33393374447337F73337F33737FFCCC333393333
              444377733337F333777FC3333339333337437333333733333373}
            NumGlyphs = 2
            TabOrder = 3
            OnClick = suggest_grazing_buttonClick
          end
        end
        object defoliation_tabsheet: TTabSheet
          Caption = 'Defoliation'
          ImageIndex = 4
          DesignSize = (
            541
            196)
          object Label8: TLabel
            Left = 0
            Top = 0
            Width = 541
            Height = 41
            Align = alTop
            AutoSize = False
            Caption = 
              'This option is used to remove most (or all) above ground biomass' +
              ',  biomatter may be removed, or usually it is applied to the soi' +
              'l surface and/or left as standing stubble, either allowing the c' +
              'rop to restart or terminate.'
            Color = clInfoBk
            ParentColor = False
            WordWrap = True
          end
          object Label19: TLabel
            Left = 0
            Top = 183
            Width = 541
            Height = 13
            Align = alBottom
            Caption = 'All above ground'
            ExplicitWidth = 80
          end
          object suggest_defoliation_button: TBitBtn
            Left = 362
            Top = 124
            Width = 177
            Height = 25
            Anchors = [akTop, akRight]
            Caption = 'Enter suggested values'
            Glyph.Data = {
              76010000424D7601000000000000760000002800000020000000100000000100
              04000000000000010000120B0000120B00001000000000000000000000000000
              800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
              FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333393333
              333333333337F3333333333333397333333333333337FF333333333333C94333
              3333333333737F333333333333C9473333333333337373F3333333333CC94433
              3333333337F7F7F3333333333CC94473333333333737F73F33333333CCC94443
              333333337F37F37F33333333CCC94447333333337337F373F333333CCCC94444
              33333337F337F337F333333CCCC94444733333373337F3373F3333CCCCC94444
              4333337F3337FF337F3333CCCCC94444473333733F7773FF73F33CCCCC393444
              443337F37737F773F7F33CCC33393374447337F73337F33737FFCCC333393333
              444377733337F333777FC3333339333337437333333733333373}
            NumGlyphs = 2
            TabOrder = 0
            OnClick = suggest_defoliation_buttonClick
          end
        end
      end
      object biomatter_fate_groupbox: TGroupBox
        Left = 0
        Top = 227
        Width = 549
        Height = 128
        Align = alBottom
        Caption = 'biomass has the following disposition '
        TabOrder = 1
        object ScrollBox1: TScrollBox
          Left = 2
          Top = 15
          Width = 545
          Height = 111
          Align = alClient
          BorderStyle = bsNone
          TabOrder = 0
          object remove_for_use_edit: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 3
            Top = 3
            Width = 522
            Height = 22
            Hint = 
              'This accounts for biomatter that is removed from the field (in a' +
              'ddition to or in lieu of any harvest index yield) that may be co' +
              'nsumed for other purposes.'
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 
              'Removed and designated for beneficial use (clipped fodder, silag' +
              'e, etc.)'
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
            OnExit = update_total_percent
          end
          object remain_as_residue_edit: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 3
            Top = 59
            Width = 522
            Height = 22
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Remains in the field laying as surface residue'
            TabOrder = 2
            OnExit = update_total_percent
          end
          object remove_for_disposal_edit: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 3
            Top = 31
            Width = 522
            Height = 22
            Hint = 
              'This is used to account for biomatter that is not harvested yiel' +
              'd, otherwise consumed or applied to the soil), such as prunings,' +
              ' chaff or corn cobs that are collected but removed during proces' +
              'sing.'
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Removed from the field and disposed (unused)'
            TabOrder = 1
            OnExit = update_total_percent
          end
          object remain_as_standing_dead_edit: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 3
            Top = 87
            Width = 522
            Height = 22
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Remains in the field as dead standing stubble/residue'
            TabOrder = 3
            OnExit = update_total_percent
          end
          object remain_as_standing_live_edit: TRNAutoParameterEditBar
            AlignWithMargins = True
            Left = 3
            Top = 115
            Width = 522
            Height = 22
            Hint = 
              'This reserves a portion of the plant as live and potentially reg' +
              'eneratable plant parts)'
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = 'Remains as live standing plant tissue '
            ParentShowHint = False
            ShowHint = True
            TabOrder = 4
            OnExit = update_total_percent
          end
        end
      end
      object select_one_mode_memo: TMemo
        Left = 399
        Top = 0
        Width = 148
        Height = 20
        Anchors = [akTop, akRight]
        BorderStyle = bsNone
        Color = clAqua
        Lines.Strings = (
          '<-- Select one of these modes')
        TabOrder = 2
      end
      object panel_biomass_fate_terminate_crop: TPanel
        Left = 0
        Top = 355
        Width = 549
        Height = 29
        Align = alBottom
        BevelOuter = bvNone
        TabOrder = 3
        DesignSize = (
          549
          29)
        object terminate_crop_label: TLabel
          Left = 120
          Top = 0
          Width = 256
          Height = 29
          AutoSize = False
          Caption = 
            'Terminating the crop kills the crop, and any remaining live biom' +
            'atter will be added to dead standing residue.'
          Color = clInfoBk
          ParentColor = False
          WordWrap = True
        end
        object Label11: TLabel
          Left = 438
          Top = 4
          Width = 8
          Height = 13
          Anchors = [akTop, akRight]
          Caption = '%'
        end
        object terminate_crop_checkbox: TRNAutoCheckBox
          Left = 8
          Top = 8
          Width = 105
          Height = 17
          Caption = 'Terminate crop'
          TabOrder = 0
          OnClick = terminate_crop_checkboxClick
        end
        object percent_total_out: TRNAutoIntegerEdit
          Left = 374
          Top = 0
          Width = 57
          Height = 24
          Alignment = taRightJustify
          Anchors = [akTop, akRight]
          Color = clRed
          Lines.Strings = (
            '0')
          TabOrder = 1
          OnEnter = update_total_percent
        end
      end
    end
    object constraints_tabsheet: TTabSheet
      Caption = 'Require conditions for Grazing/Clipping '
      ImageIndex = 2
      object min_LAI_required_edit: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 3
        Top = 3
        Width = 543
        Height = 22
        Hint = 'This parameter is used for repeated clipping operations.'
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Minimum LAI required for clipping'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
      end
      object min_biomass_required_edit: TRNAutoParameterEditBar
        AlignWithMargins = True
        Left = 3
        Top = 31
        Width = 543
        Height = 22
        Hint = 'This parameter is used for repeated clipping operations.'
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Caption = 'Minimum biomass required for clipping'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
      end
    end
  end
end
