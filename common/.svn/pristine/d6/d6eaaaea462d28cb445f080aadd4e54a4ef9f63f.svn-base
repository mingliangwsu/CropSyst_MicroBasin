object geolocation_form: Tgeolocation_form
  Left = 550
  Top = 274
  Align = alClient
  Caption = 'geolocation_form'
  ClientHeight = 207
  ClientWidth = 324
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object geolocation_pagecontrol: TPageControl
    Left = 0
    Top = 41
    Width = 324
    Height = 166
    Hint = 
      'Coordinates of the weather station may be entered in any one of ' +
      'these coordinate systems.  Entering values for one will automati' +
      'cally calculate the others.'
    ActivePage = position_tabsheet
    Align = alClient
    ParentShowHint = False
    ShowHint = True
    TabOrder = 0
    object position_tabsheet: TTabSheet
      Caption = 'Position'
      DesignSize = (
        316
        138)
      object elevation_label: TLabel
        Left = 4
        Top = 86
        Width = 44
        Height = 13
        Caption = 'Elevation'
      end
      object Label8: TLabel
        Left = 152
        Top = 86
        Width = 8
        Height = 13
        Caption = 'm'
      end
      object screening_height_label: TLabel
        Left = 4
        Top = 110
        Width = 80
        Height = 13
        Caption = 'Screening height'
      end
      object Label9: TLabel
        Left = 152
        Top = 110
        Width = 8
        Height = 13
        Caption = 'm'
      end
      object elevation_edit: TRNAutoFloatEdit
        Left = 88
        Top = 80
        Width = 57
        Height = 24
        Alignment = taRightJustify
        Lines.Strings = (
          '0')
        TabOrder = 1
      end
      object screening_height_edit: TRNAutoFloatEdit
        Left = 88
        Top = 106
        Width = 57
        Height = 24
        Alignment = taRightJustify
        Lines.Strings = (
          '0')
        TabOrder = 2
      end
      object coordinates_pagecontrol: TPageControl
        Left = 0
        Top = 0
        Width = 316
        Height = 81
        ActivePage = coord_DMS_tabsheet
        Align = alTop
        Style = tsButtons
        TabOrder = 0
        object coord_DMS_tabsheet: TTabSheet
          Caption = 'Degrees-Minutes-Seconds'
          object latitude_DMS_label: TLabel
            Left = 4
            Top = 8
            Width = 38
            Height = 13
            Caption = 'Latitude'
          end
          object Label55: TLabel
            Left = 106
            Top = 0
            Width = 5
            Height = 20
            Caption = #176
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -16
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
          end
          object Label56: TLabel
            Left = 148
            Top = 0
            Width = 3
            Height = 20
            Caption = #39
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -16
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
          end
          object Label57: TLabel
            Left = 220
            Top = 0
            Width = 5
            Height = 13
            AutoSize = False
            Caption = '"'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -16
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
          end
          object Label58: TLabel
            Left = 106
            Top = 24
            Width = 5
            Height = 20
            Caption = #176
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -16
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
          end
          object Label59: TLabel
            Left = 148
            Top = 24
            Width = 3
            Height = 20
            Caption = #39
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -16
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
          end
          object Label60: TLabel
            Left = 220
            Top = 24
            Width = 5
            Height = 13
            AutoSize = False
            Caption = '"'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -16
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
          end
          object longitude_DMS_label: TLabel
            Left = 4
            Top = 32
            Width = 47
            Height = 13
            Caption = 'Longitude'
          end
          object lat_deg_edit: TRNAutoIntegerEdit
            Left = 78
            Top = 0
            Width = 25
            Height = 24
            Alignment = taRightJustify
            Lines.Strings = (
              '0')
            TabOrder = 0
            WantReturns = False
            OnExit = latitude_degminsec_onexit
          end
          object lat_min_edit: TRNAutoIntegerEdit
            Left = 118
            Top = 0
            Width = 25
            Height = 24
            Alignment = taRightJustify
            Lines.Strings = (
              '0')
            TabOrder = 1
            WantReturns = False
            OnExit = latitude_degminsec_onexit
          end
          object lat_sec_edit: TRNAutoFloatEdit
            Left = 158
            Top = 0
            Width = 54
            Height = 24
            Alignment = taRightJustify
            Lines.Strings = (
              '0')
            TabOrder = 2
            WantReturns = False
            OnExit = latitude_degminsec_onexit
          end
          object lat_dir_combobox: TComboBox
            Left = 228
            Top = 0
            Width = 65
            Height = 21
            TabOrder = 3
            Text = 'North'
            OnExit = latitude_degminsec_onexit
            Items.Strings = (
              'South'
              'North')
          end
          object long_deg_edit: TRNAutoIntegerEdit
            Left = 78
            Top = 24
            Width = 25
            Height = 24
            Alignment = taRightJustify
            Lines.Strings = (
              '0')
            TabOrder = 4
            WantReturns = False
            OnExit = longitude_degmin_sec_onexit
          end
          object long_min_edit: TRNAutoIntegerEdit
            Left = 118
            Top = 24
            Width = 25
            Height = 24
            Alignment = taRightJustify
            Lines.Strings = (
              '0')
            TabOrder = 5
            WantReturns = False
            OnExit = longitude_degmin_sec_onexit
          end
          object long_sec_edit: TRNAutoFloatEdit
            Left = 158
            Top = 24
            Width = 54
            Height = 24
            Alignment = taRightJustify
            Lines.Strings = (
              '0')
            TabOrder = 6
            WantReturns = False
            OnExit = longitude_degmin_sec_onexit
          end
          object long_dir_combobox: TComboBox
            Left = 228
            Top = 24
            Width = 65
            Height = 21
            TabOrder = 7
            Text = 'West'
            OnExit = longitude_degmin_sec_onexit
            Items.Strings = (
              'West'
              'East')
          end
        end
        object coord_dec_deg_tabsheet: TTabSheet
          Caption = 'Decimal degrees'
          ImageIndex = 1
          object Label4: TLabel
            Left = 4
            Top = 8
            Width = 38
            Height = 13
            Caption = 'Latitude'
          end
          object Label5: TLabel
            Left = 152
            Top = 8
            Width = 77
            Height = 13
            Caption = 'decimal degrees'
          end
          object Label7: TLabel
            Left = 4
            Top = 32
            Width = 47
            Height = 13
            Caption = 'Longitude'
          end
          object Label6: TLabel
            Left = 152
            Top = 32
            Width = 77
            Height = 13
            Caption = 'decimal degrees'
          end
          object latitude_decdeg_edit: TRNAutoFloatEdit
            Left = 78
            Top = 0
            Width = 67
            Height = 24
            Alignment = taRightJustify
            Lines.Strings = (
              '0')
            TabOrder = 0
            OnExit = latitude_decdeg_onexit
          end
          object longitude_decdeg_edit: TRNAutoFloatEdit
            Left = 78
            Top = 24
            Width = 67
            Height = 24
            Alignment = taRightJustify
            Lines.Strings = (
              '0')
            TabOrder = 1
            OnExit = longitude_decdeg_onexit
          end
        end
        object coord_UTM_tabsheet: TTabSheet
          Caption = 'UTM'
          ImageIndex = 2
          DesignSize = (
            308
            50)
          object Label2: TLabel
            Left = 80
            Top = 4
            Width = 40
            Height = 13
            Caption = 'Northing'
          end
          object utm_northing_units: TLabel
            Left = 286
            Top = 4
            Width = 8
            Height = 13
            Caption = 'm'
          end
          object utm_zone_label: TLabel
            Left = 0
            Top = 4
            Width = 25
            Height = 13
            Caption = 'Zone'
          end
          object Label3: TLabel
            Left = 286
            Top = 26
            Width = 8
            Height = 13
            Caption = 'm'
          end
          object utm_easting_label: TLabel
            Left = 80
            Top = 26
            Width = 35
            Height = 13
            Caption = 'Easting'
          end
          object utm_northing_edit: TRNAutoFloatEdit
            Left = 128
            Top = 0
            Width = 156
            Height = 24
            Alignment = taRightJustify
            Anchors = [akLeft, akTop, akRight]
            Lines.Strings = (
              '0')
            TabOrder = 2
            OnExit = utm_onexit
          end
          object utm_zone_edit: TRNAutoIntegerEdit
            Left = 30
            Top = 0
            Width = 41
            Height = 24
            Alignment = taRightJustify
            Lines.Strings = (
              '0')
            TabOrder = 0
            OnExit = utm_onexit
          end
          object utm_zone_desg_edit: TEdit
            Left = 30
            Top = 24
            Width = 17
            Height = 21
            MaxLength = 1
            TabOrder = 1
            Text = 'Z'
            OnChange = utm_onexit
          end
          object utm_easting_edit: TRNAutoFloatEdit
            Left = 128
            Top = 24
            Width = 156
            Height = 24
            Alignment = taRightJustify
            Anchors = [akLeft, akTop, akRight]
            Lines.Strings = (
              '0')
            TabOrder = 3
            OnExit = utm_onexit
          end
        end
      end
      object button_google_maps: TBitBtn
        Left = 232
        Top = 87
        Width = 81
        Height = 42
        Hint = 
          'Displays this location using Google Maps (Requires a Web browser' +
          ' and internet connection)'
        Anchors = [akRight, akBottom]
        Caption = 'Map'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        Glyph.Data = {
          36080000424D3608000000000000360400002800000020000000200000000100
          08000000000000040000130B0000130B0000000100000001000047BD7C00FFFF
          FF00C07E570081E7E9008DA7BD004252DC0046C07D0061C78F001C1B7400C386
          620095AEC20047BC7D00C07F580084E9EF0041BB78008EA1B90082EBEC007FF0
          EF00D7EFE2008AE7E9003EBA7600D0ECDC00C57549005DCCA6003DB66800F9FD
          FB0084D9DF0076F8FC004151DC0047C574002FB66D0080EEEE00A5DEBE00E9F7
          EF008AEEF9004657E60093AEBA003847E00048CA6F0083DFE400BD774E00E8F7
          EF00B6693A0035B8710091D1C70027B36700424CE100ACDFC20099B4B8004247
          E500C5E9D50087F3EA00D1A288008AB8C90055BF830078CB9C00C86F41001815
          6A008F9CB6006BC7920072E4E600BDE6CF0048CD6C00C37B54006E85CA00AFEF
          F100C6F4F500829BC2008AD4AB00EBD8CE0046A6970087C7D3003741BC0097D6
          B2009CECEE008BD9D100CA6D3E00459BA1005686E00086D1DA004C5ED8008BB0
          C300BA896800F8F1ED00413DEC00CD997B00282C94004361D400DEBCAB00458A
          B1005567D700A1B5A30099C5BA00EBD7CC00A8AD9B00B29C84007CC7BC00B6A0
          87002734E500D4F6F70047C79F00A4B4A500ACA48E00BAEDE60094C9BF00B890
          7300E4C7B8003039AA00609AE30046AE8F0070C1E6004375C400447CBA005DD4
          9D0066AAE30046A994004367CF004592AD004470CB007990C7006479D0007AD3
          E8005C70D20069B9EB0086FFF100526CED00469F9E0064327700130C3B00DBC0
          2D00C5167D00AAB2460094B03800F5C14A0084C50F00D1E8D600CB469E001F0D
          D0005CA81C0084E4DA0048908400ED16BA00C143AD00DF3773002EB8000007EE
          C50002190A00F3C9860089D2C300CAD56600D7692100B43AED00B7588500A80E
          AC008B438B00D3B81100F99AD200439CC4009E57000078556C00FF8951009F1D
          DA0034422C00F37A530048920B00E93DE200A47DA000D40B2D00720D5500F101
          280049D60F00E77A6800B0995A00FD8E49003FEC6400919067007813830037C4
          27004115C500E9F72A000929D600FA64CF00E93373005E1D890020C96F004DBE
          2300F0A91D00A0602B003498E90084D80700366A770023126C0060F7BB00F42A
          3300B6BB84002479A900F7F24800A8E1E700DDA23E0074843200084E5E00AB11
          0C00BE7D0C00AD9D7E00A9E71B0066F4A400C1B6F1004D7B600048C853002C3F
          0800DC90F400E1931F00F8214B0041D101007E21F4007CDBC500E48653005C57
          81004638B600B300180047461F0090B4F100E443E100653675005F1E89007A5C
          E90011A16E00145CF400A830B4004B176F007E4EE4007BBA2B0022129A006097
          1D00466FC0004110CA00D285CF007DC8630078B279005BF0AA0096F0E900B173
          2900D01AB200D3B7E600A5F1EF002391DC0010F5890008514B00FDD95F0098F7
          AE00D12F270024E2FB009AD1960011240C008BA06300D4F74900070022030303
          030C0202020202020201010102020202020202020202020202020700000D0303
          0303020202020202280101010202020202020202020202020202070000000D03
          0303030202020202010101010202020202020202020202020202320000000022
          030303030C020C01010101010202020202020202020202020C68012100000000
          220303030328010101010101020202020202020202023F1103030101013D0000
          002203033C0101010101012A0202020202020202090303030303320101010101
          0101010101010101010153020202020202025C03030303030303070000000015
          0101010101010101015502020202024C03030303030303034F04070000000000
          00150101010101014A0202020C2C030303030303030304040404070000000000
          000101010101013C03033F1103030303030303110F0404040404070000000000
          2B01010101012203030303030303030303040404040404040404070000000000
          1E0101010114000D0303030303031F0F04040404040404040404070000001E1E
          1E01010101140000220303030304040404040404040404040404071E01010101
          0101010101010000000D03030303040404045A04040404040404010101010101
          1E0B000001010100000022030303030404402E04040404040404010101011900
          00000000000101011400002203030303041C0504040404040404010101010000
          00000000002D0101010000000D030303030505040404040404040101012B0000
          0000000000000101010100000022030331050550040404040404010101000000
          00000000000001010101000000000D0305050505040404040404010120000000
          000000000000010101013700000000050505050525040404040401012B000000
          000000000000010101012900000074050505050505300404040401010B000000
          00000000000E0101010129000026050505050505050504040404010100000000
          00000000002F010101014400002E050505232305050574040404010100000000
          000000000001010101010E00000505053908082305050503040401012D000000
          000000002D010101010100000B05050508080808050505030304010101000000
          0000000001010101010B00000005050523080805050505030303490101010000
          00000B01010101012D0000000054050505050505050523030303072B01010112
          3D0101010101010101011400000B05050505050505050B0D03030700000B1201
          0101010101010101010101012B000B2E05050505310000000D03070000000000
          00000E0E0E1414140E0E0E0E0E0000001D6D6D00000000000022070000000000
          00000000000000000000000000000000000000000000000000003B0707070707
          0707070707070707070707070707070707070707070707070707}
        ParentFont = False
        TabOrder = 3
        OnClick = button_google_mapsClick
      end
    end
    object region_tabsheet: TTabSheet
      Hint = 
        'This information is not used by CropSyst or ClimGen, but if ofte' +
        'n imported by the weather format import utilities.  It is recomm' +
        'ended to provide this data to adequately document the weather da' +
        'ta.'
      Caption = 'Region'
      ImageIndex = 1
      ParentShowHint = False
      ShowHint = True
      DesignSize = (
        316
        138)
      object country_label: TLabel
        Left = 8
        Top = 0
        Width = 36
        Height = 13
        Caption = 'Country'
      end
      object state_label: TLabel
        Left = 8
        Top = 48
        Width = 72
        Height = 13
        Caption = 'State/Province'
      end
      object Label1: TLabel
        Left = 8
        Top = 96
        Width = 72
        Height = 13
        Caption = 'County/Region'
      end
      object country_name_edit: TRNAutoStringEdit
        Left = 88
        Top = 24
        Width = 227
        Height = 21
        Anchors = [akLeft, akTop, akRight]
        TabOrder = 1
      end
      object state_code_edit: TRNAutoStringEdit
        Left = 88
        Top = 72
        Width = 227
        Height = 21
        Anchors = [akLeft, akTop, akRight]
        TabOrder = 3
      end
      object county_code_edit: TRNAutoStringEdit
        Left = 88
        Top = 120
        Width = 227
        Height = 21
        Anchors = [akLeft, akTop, akRight]
        TabOrder = 5
      end
      object country_ISO3166_code_combobox: TComboBox
        Left = 88
        Top = 0
        Width = 227
        Height = 22
        Anchors = [akLeft, akTop, akRight]
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        Text = '  0  (Unknown) '
        OnChange = country_ISO3166_code_combobox_onchange
        Items.Strings = (
          '  0  (Unknown) '
          '840  United States'
          '  4  Afghanistan'
          '  8  Albania'
          ' 12  Algeria'
          ' 16  American Samoa'
          ' 20  Andorra'
          ' 24  Angola'
          '660  Anguilla'
          ' 10  Antarctica'
          ' 28  Antigua and Barbuda'
          ' 32  Argentina'
          ' 51  Armenia'
          '533  Aruba'
          ' 36  Australia'
          ' 40  Austria'
          ' 31  Azerbaijan'
          ' 44  Bahamas'
          ' 48  Bahrain'
          ' 50  Bangladesh'
          ' 52  Barbados'
          '112  Belarus'
          ' 56  Belgium'
          ' 84  Belize'
          '204  Benin'
          ' 60  Bermuda'
          ' 64  Bhutan'
          ' 68  Bolivia'
          ' 70  Bosnia and Herzegowina'
          ' 72  Botswana'
          ' 74  Bouvet Island'
          ' 76  Brazil'
          ' 86  British Indian Ocean Territory'
          ' 96  Brunei Darussalam'
          '100  Bulgaria'
          '854  Burkina Faso'
          '108  Burundi'
          '116  Cambodia'
          '120  Cameroon'
          '124  Canada'
          '132  Cape Verde'
          '136  Cayman Islands'
          '140  Central African Republic'
          '148  Chad'
          '152  Chile'
          '156  China'
          '162  Christmas Island'
          '166  Cocos (Keeling) Islands'
          '170  Colombia'
          '174  Comoros'
          '178  Congo'
          '180  Congo, The Democratic Republic Of The'
          '184  Cook Islands'
          '188  Costa Rica'
          '384  Cote D'#39'Ivoire'
          '191  Croatia (Local Name: Hrvatska)'
          '192  Cuba'
          '196  Cyprus'
          '203  Czech Republic'
          '208  Denmark'
          '262  Djibouti'
          '212  Dominica'
          '214  Dominican Republic'
          '626  East Timor'
          '218  Ecuador'
          '818  Egypt'
          '222  El Salvador'
          '226  Equatorial Guinea'
          '232  Eritrea'
          '233  Estonia'
          '231  Ethiopia'
          '238  Falkland Islands (Malvinas)'
          '234  Faroe Islands'
          '242  Fiji'
          '246  Finland'
          '250  France'
          '249  France, Metropolitan'
          '254  French Guiana'
          '258  French Polynesia'
          '260  French Southern Territories'
          '266  Gabon'
          '270  Gambia'
          '268  Georgia'
          '276  Germany'
          '288  Ghana'
          '292  Gibraltar'
          '300  Greece'
          '304  Greenland'
          '308  Grenada'
          '312  Guadeloupe'
          '316  Guam'
          '320  Guatemala'
          '324  Guinea'
          '624  Guinea-Bissau'
          '328  Guyana'
          '332  Haiti'
          '334  Heard and Mc Donald Islands'
          '336  Holy See (Vatican City State)'
          '340  Honduras'
          '344  Hong Kong'
          '348  Hungary'
          '352  Iceland'
          '356  India'
          '360  Indonesia'
          '364  Iran (Islamic Republic Of)'
          '368  Iraq'
          '372  Ireland'
          '376  Israel'
          '380  Italy'
          '388  Jamaica'
          '392  Japan'
          '400  Jordan'
          '398  Kazakhstan'
          '404  Kenya'
          '296  Kiribati'
          '408  Korea, Democratic People'#39'S Republic Of'
          '410  Korea, Republic Of'
          '414  Kuwait'
          '417  Kyrgyzstan'
          '418  Lao People'#39'S Democratic Republic'
          '428  Latvia'
          '422  Lebanon'
          '426  Lesotho'
          '430  Liberia'
          '434  Libyan Arab Jamahiriya'
          '438  Liechtenstein'
          '440  Lithuania'
          '442  Luxembourg'
          '446  Macau'
          '807  Macedonia, The Former Yugoslav Republic Of'
          '450  Madagascar'
          '454  Malawi'
          '458  Malaysia'
          '462  Maldives'
          '466  Mali'
          '470  Malta'
          '584  Marshall Islands'
          '474  Martinique'
          '478  Mauritania'
          '480  Mauritius'
          '175  Mayotte'
          '484  Mexico'
          '583  Micronesia, Federated States Of'
          '498  Moldova, Republic Of'
          '492  Monaco'
          '496  Mongolia'
          '500  Montserrat'
          '504  Morocco'
          '508  Mozambique'
          '104  Myanmar'
          '516  Namibia'
          '520  Nauru'
          '524  Nepal'
          '528  Netherlands'
          '530  Netherlands Antilles'
          '540  New Caledonia'
          '554  New Zealand'
          '558  Nicaragua'
          '562  Niger'
          '566  Nigeria'
          '570  Niue'
          '574  Norfolk Island'
          '580  Northern Mariana Islands'
          '578  Norway'
          '512  Oman'
          '586  Pakistan'
          '585  Palau'
          '591  Panama'
          '598  Papua New Guinea'
          '600  Paraguay'
          '604  Peru'
          '608  Philippines'
          '612  Pitcairn'
          '616  Poland'
          '620  Portugal'
          '630  Puerto Rico'
          '634  Qatar'
          '638  Reunion'
          '642  Romania'
          '643  Russian Federation'
          '646  Rwanda'
          '659  Saint Kitts and Nevis'
          '662  Saint Lucia'
          '670  Saint Vincent and The Grenadines'
          '882  Samoa'
          '674  San Marino'
          '678  Sao Tome and Principe'
          '682  Saudi Arabia'
          '686  Senegal'
          '690  Seychelles'
          '694  Sierra Leone'
          '702  Singapore'
          '703  Slovakia (Slovak Republic)'
          '705  Slovenia'
          ' 90  Solomon Islands'
          '706  Somalia'
          '710  South Africa'
          '239  South Georgia and The South Sandwich Islands'
          '724  Spain'
          '144  Sri Lanka'
          '654  St. Helena'
          '666  St. Pierre and Miquelon'
          '736  Sudan'
          '740  Suriname'
          '744  Svalbard and Jan Mayen Islands'
          '748  Swaziland'
          '752  Sweden'
          '756  Switzerland'
          '760  Syrian Arab Republic'
          '158  Taiwan, Province Of China'
          '762  Tajikistan'
          '834  Tanzania, United Republic Of'
          '764  Thailand'
          '768  Togo'
          '772  Tokelau'
          '776  Tonga'
          '780  Trinidad and Tobago'
          '788  Tunisia'
          '792  Turkey'
          '795  Turkmenistan'
          '796  Turks and Caicos Islands'
          '798  Tuvalu'
          '800  Uganda'
          '804  Ukraine'
          '784  United Arab Emirates'
          '826  United Kingdom'
          '840  United States'
          '581  United States Minor Outlying Islands'
          '858  Uruguay'
          '860  Uzbekistan'
          '548  Vanuatu'
          '862  Venezuela'
          '704  Viet Nam'
          ' 92  Virgin Islands (British)'
          '850  Virgin Islands (U.S.)'
          '876  Wallis and Futuna Islands'
          '732  Western Sahara'
          '887  Yemen'
          '891  Yugoslavia'
          '894  Zambia'
          '716  Zimbabwe')
      end
      object US_state_FIPS_combobox: TComboBox
        Left = 88
        Top = 48
        Width = 227
        Height = 22
        Anchors = [akLeft, akTop, akRight]
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        TabOrder = 2
        Text = ' 0 (Unknown)'
        OnChange = US_state_FIPS_combobox_onchange
        Items.Strings = (
          ' 0 (Unknown)'
          ' 2  Alaska'
          ' 1  Alabama'
          ' 5  Arkansas'
          '60  American Samoa'
          ' 4  Arizona'
          ' 6  California'
          ' 8  Colorado'
          ' 9  Connecticut'
          '11  District Of Columbia'
          '10  Delaware'
          '12  Florida'
          '13  Georgia'
          '66  Guam'
          '15  Hawaii'
          '19  Iowa'
          '16  Idaho'
          '17  Illinois'
          '18  Indiana'
          '20  Kansas'
          '21  Kentucky'
          '22  Louisiana'
          '25  Massachusetts'
          '24  Maryland'
          '23  Maine'
          '26  Michigan'
          '27  Minnesota'
          '29  Missouri'
          '28  Mississippi'
          '30  Montana'
          '37  North Carolina'
          '38  North Dakota'
          '31  Nebraska'
          '33  New Hampshire'
          '34  New Jersey'
          '35  New Mexico'
          '32  Nevada'
          '36  New York'
          '39  Ohio'
          '40  Oklahoma'
          '41  Oregon'
          '42  Pennsylvania'
          '72  Puerto Rico'
          '44  Rhode Island'
          '45  South Carolina'
          '46  South Dakota'
          '47  Tennessee'
          '48  Texas'
          '49  Utah'
          '51  Virginia'
          '78  Virgin Islands'
          '50  Vermont'
          '53  Washington'
          '55  Wisconsin'
          '54  West Virginia'
          '56  Wyoming')
      end
      object county_code_combobox: TComboBox
        Left = 88
        Top = 96
        Width = 227
        Height = 22
        Anchors = [akLeft, akTop, akRight]
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        TabOrder = 4
        Text = 'County code not yet implemented'
        Visible = False
      end
    end
    object station_tabsheet: TTabSheet
      Hint = 
        'This information is not used by CropSyst or ClimGen, but if ofte' +
        'n imported by the weather format import utilities.  It is recomm' +
        'ended to provide this data to adequately document the weather da' +
        'ta source'
      Caption = 'Weather station'
      ImageIndex = 2
      ParentShowHint = False
      ShowHint = True
      DesignSize = (
        316
        138)
      object station_ID_code_label: TLabel
        Left = 6
        Top = 44
        Width = 87
        Height = 13
        Caption = 'Identification code'
      end
      object station_name_label: TLabel
        Left = 64
        Top = 74
        Width = 28
        Height = 13
        Caption = 'Name'
      end
      object station_number_label: TLabel
        Left = 56
        Top = 14
        Width = 37
        Height = 13
        Caption = 'Number'
      end
      object station_ID_code_edit: TRNAutoStringEdit
        Left = 96
        Top = 40
        Width = 219
        Height = 21
        Anchors = [akLeft, akTop, akRight]
        TabOrder = 1
        Text = 'station_ID_code_edit'
      end
      object station_name_edit: TRNAutoStringEdit
        Left = 96
        Top = 72
        Width = 219
        Height = 21
        Anchors = [akLeft, akTop, akRight]
        TabOrder = 2
        Text = 'station_name_edit'
      end
      object station_number_edit: TEdit
        Left = 96
        Top = 10
        Width = 121
        Height = 21
        TabOrder = 0
        Text = '0'
        OnChange = station_number_edit_onchange
      end
    end
  end
  object groupbox_description: TGroupBox
    Left = 0
    Top = 0
    Width = 324
    Height = 41
    Align = alTop
    Caption = 'Description of the location or weather station'
    TabOrder = 1
    DesignSize = (
      324
      41)
    object description_edit: TRNAutoStringEdit
      Left = 8
      Top = 16
      Width = 308
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 0
      Text = 'description_edit'
    end
  end
end
