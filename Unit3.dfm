object Form3: TForm3
  Left = 275
  Top = 119
  BorderStyle = bsDialog
  Caption = 'Settings'
  ClientHeight = 224
  ClientWidth = 334
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 16
    Top = 8
    Width = 305
    Height = 177
    Caption = 'Passwords'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    object Label1: TLabel
      Left = 16
      Top = 78
      Width = 184
      Height = 14
      Caption = 'San Andreas Installation Location:'
    end
    object Label2: TLabel
      Left = 16
      Top = 126
      Width = 57
      Height = 14
      Caption = 'Language:'
    end
    object CheckBox1: TCheckBox
      Left = 16
      Top = 24
      Width = 281
      Height = 17
      Caption = 'Auto-Save Server Passwords'
      TabOrder = 0
    end
    object CheckBox2: TCheckBox
      Left = 16
      Top = 48
      Width = 281
      Height = 17
      Caption = 'Auto-Save Rcon Passwords'
      TabOrder = 1
    end
    object Edit1: TEdit
      Left = 16
      Top = 96
      Width = 257
      Height = 22
      Enabled = False
      TabOrder = 2
    end
    object Button3: TButton
      Left = 277
      Top = 96
      Width = 20
      Height = 20
      Caption = '...'
      TabOrder = 3
      OnClick = Button3Click
    end
    object ComboBox1: TComboBox
      Left = 16
      Top = 144
      Width = 145
      Height = 22
      ItemHeight = 14
      TabOrder = 4
    end
  end
  object Button1: TButton
    Left = 96
    Top = 192
    Width = 75
    Height = 25
    Caption = 'Save'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 248
    Top = 192
    Width = 75
    Height = 25
    Caption = 'Cancel'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    OnClick = Button2Click
  end
  object Button4: TButton
    Left = 16
    Top = 193
    Width = 75
    Height = 25
    Caption = 'OK'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    OnClick = Button4Click
  end
  object OpenDialog1: TOpenDialog
    Left = 184
    Top = 188
  end
end
