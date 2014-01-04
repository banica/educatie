VERSION 5.00
Begin VB.Form simulare 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Simulare"
   ClientHeight    =   3075
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   11040
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3075
   ScaleWidth      =   11040
   StartUpPosition =   2  'CenterScreen
   Begin VB.Timer second 
      Enabled         =   0   'False
      Interval        =   6000
      Left            =   1200
      Top             =   2160
   End
   Begin VB.Timer main 
      Interval        =   2500
      Left            =   600
      Top             =   2160
   End
   Begin VB.Line linie 
      Index           =   0
      X1              =   3720
      X2              =   3840
      Y1              =   1080
      Y2              =   960
   End
   Begin VB.Line linie 
      Index           =   1
      X1              =   5280
      X2              =   5400
      Y1              =   1680
      Y2              =   1560
   End
   Begin VB.Line linie 
      Index           =   2
      X1              =   2880
      X2              =   3000
      Y1              =   1680
      Y2              =   1560
   End
   Begin VB.Line linie 
      Index           =   3
      X1              =   1800
      X2              =   1920
      Y1              =   480
      Y2              =   360
   End
   Begin VB.Line linie 
      Index           =   4
      X1              =   10200
      X2              =   10320
      Y1              =   480
      Y2              =   360
   End
   Begin VB.Line linie 
      Index           =   5
      X1              =   8880
      X2              =   9000
      Y1              =   480
      Y2              =   360
   End
   Begin VB.Line linie 
      Index           =   6
      X1              =   6600
      X2              =   6720
      Y1              =   480
      Y2              =   360
   End
   Begin VB.Line linie 
      Index           =   7
      X1              =   3840
      X2              =   3720
      Y1              =   960
      Y2              =   840
   End
   Begin VB.Line linie 
      Index           =   8
      X1              =   3120
      X2              =   3000
      Y1              =   1680
      Y2              =   1560
   End
   Begin VB.Line linie 
      Index           =   9
      X1              =   5520
      X2              =   5400
      Y1              =   1680
      Y2              =   1560
   End
   Begin VB.Line linie 
      Index           =   10
      X1              =   10200
      X2              =   10080
      Y1              =   480
      Y2              =   360
   End
   Begin VB.Line linie 
      Index           =   11
      X1              =   8880
      X2              =   8760
      Y1              =   480
      Y2              =   360
   End
   Begin VB.Line linie 
      Index           =   12
      X1              =   1800
      X2              =   1680
      Y1              =   480
      Y2              =   360
   End
   Begin VB.Line linie 
      Index           =   13
      X1              =   6600
      X2              =   6480
      Y1              =   480
      Y2              =   360
   End
   Begin VB.Line linie 
      Index           =   14
      X1              =   8280
      X2              =   8160
      Y1              =   1080
      Y2              =   960
   End
   Begin VB.Line linie 
      Index           =   15
      X1              =   8160
      X2              =   8280
      Y1              =   960
      Y2              =   840
   End
   Begin VB.Line linie 
      Index           =   16
      X1              =   8160
      X2              =   8640
      Y1              =   960
      Y2              =   960
   End
   Begin VB.Line linie 
      Index           =   17
      X1              =   10200
      X2              =   10200
      Y1              =   480
      Y2              =   120
   End
   Begin VB.Line linie 
      Index           =   18
      X1              =   10200
      X2              =   10800
      Y1              =   120
      Y2              =   120
   End
   Begin VB.Line linie 
      Index           =   19
      X1              =   10800
      X2              =   10800
      Y1              =   120
      Y2              =   1800
   End
   Begin VB.Line linie 
      Index           =   20
      X1              =   10800
      X2              =   10200
      Y1              =   1800
      Y2              =   1800
   End
   Begin VB.Line linie 
      Index           =   21
      X1              =   10200
      X2              =   10200
      Y1              =   1560
      Y2              =   1800
   End
   Begin VB.Line linie 
      Index           =   22
      X1              =   5400
      X2              =   5400
      Y1              =   1560
      Y2              =   1800
   End
   Begin VB.Line linie 
      Index           =   23
      X1              =   5400
      X2              =   7800
      Y1              =   1800
      Y2              =   1800
   End
   Begin VB.Line linie 
      Index           =   24
      X1              =   7800
      X2              =   7800
      Y1              =   1560
      Y2              =   1800
   End
   Begin VB.Line linie 
      Index           =   25
      X1              =   3000
      X2              =   3000
      Y1              =   1560
      Y2              =   1920
   End
   Begin VB.Line linie 
      Index           =   26
      X1              =   3000
      X2              =   6600
      Y1              =   1920
      Y2              =   1920
   End
   Begin VB.Line linie 
      Index           =   27
      X1              =   6600
      X2              =   6600
      Y1              =   1560
      Y2              =   1920
   End
   Begin VB.Line linie 
      Index           =   28
      X1              =   8880
      X2              =   8880
      Y1              =   480
      Y2              =   240
   End
   Begin VB.Line linie 
      Index           =   29
      X1              =   8880
      X2              =   5400
      Y1              =   240
      Y2              =   240
   End
   Begin VB.Line linie 
      Index           =   39
      X1              =   5400
      X2              =   5400
      Y1              =   480
      Y2              =   240
   End
   Begin VB.Line linie 
      Index           =   30
      X1              =   6600
      X2              =   6600
      Y1              =   480
      Y2              =   120
   End
   Begin VB.Line linie 
      Index           =   31
      X1              =   6600
      X2              =   4200
      Y1              =   120
      Y2              =   120
   End
   Begin VB.Line linie 
      Index           =   32
      X1              =   4200
      X2              =   4200
      Y1              =   480
      Y2              =   120
   End
   Begin VB.Line linie 
      Index           =   33
      X1              =   3360
      X2              =   3840
      Y1              =   960
      Y2              =   960
   End
   Begin VB.Line linie 
      Index           =   34
      X1              =   1800
      X2              =   1800
      Y1              =   480
      Y2              =   120
   End
   Begin VB.Line linie 
      Index           =   35
      X1              =   1800
      X2              =   1320
      Y1              =   120
      Y2              =   120
   End
   Begin VB.Line linie 
      Index           =   36
      X1              =   1320
      X2              =   1320
      Y1              =   120
      Y2              =   1920
   End
   Begin VB.Line linie 
      Index           =   37
      X1              =   1320
      X2              =   1800
      Y1              =   1920
      Y2              =   1920
   End
   Begin VB.Line linie 
      Index           =   38
      X1              =   1800
      X2              =   1800
      Y1              =   1560
      Y2              =   1920
   End
   Begin VB.Image imagine 
      Height          =   900
      Left            =   3720
      Picture         =   "simulare.frx":0000
      Top             =   2040
      Width           =   7200
   End
   Begin VB.Label Label4 
      Alignment       =   1  'Right Justify
      Caption         =   "Masca:"
      Height          =   375
      Left            =   120
      TabIndex        =   27
      Top             =   1320
      Width           =   975
   End
   Begin VB.Label Label3 
      Alignment       =   1  'Right Justify
      Caption         =   "Variabila:"
      Height          =   375
      Left            =   120
      TabIndex        =   26
      Top             =   960
      Width           =   975
   End
   Begin VB.Label Label2 
      Alignment       =   1  'Right Justify
      Caption         =   "Coeficient:"
      Height          =   375
      Left            =   120
      TabIndex        =   25
      Top             =   600
      Width           =   975
   End
   Begin VB.Label masca 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   7
      Left            =   9840
      TabIndex        =   24
      Top             =   1200
      Width           =   735
   End
   Begin VB.Label masca 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   6
      Left            =   8640
      TabIndex        =   23
      Top             =   1200
      Width           =   735
   End
   Begin VB.Label masca 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   5
      Left            =   7440
      TabIndex        =   22
      Top             =   1200
      Width           =   735
   End
   Begin VB.Label masca 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   4
      Left            =   6240
      TabIndex        =   21
      Top             =   1200
      Width           =   735
   End
   Begin VB.Label masca 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   3
      Left            =   5040
      TabIndex        =   20
      Top             =   1200
      Width           =   735
   End
   Begin VB.Label masca 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   2
      Left            =   3840
      TabIndex        =   19
      Top             =   1200
      Width           =   735
   End
   Begin VB.Label masca 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   1
      Left            =   2640
      TabIndex        =   18
      Top             =   1200
      Width           =   735
   End
   Begin VB.Label variabila 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   7
      Left            =   9840
      TabIndex        =   17
      Top             =   840
      Width           =   735
   End
   Begin VB.Label variabila 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   6
      Left            =   8640
      TabIndex        =   16
      Top             =   840
      Width           =   735
   End
   Begin VB.Label variabila 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   5
      Left            =   7440
      TabIndex        =   15
      Top             =   840
      Width           =   735
   End
   Begin VB.Label variabila 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   4
      Left            =   6240
      TabIndex        =   14
      Top             =   840
      Width           =   735
   End
   Begin VB.Label variabila 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   3
      Left            =   5040
      TabIndex        =   13
      Top             =   840
      Width           =   735
   End
   Begin VB.Label variabila 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   2
      Left            =   3840
      TabIndex        =   12
      Top             =   840
      Width           =   735
   End
   Begin VB.Label variabila 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   1
      Left            =   2640
      TabIndex        =   11
      Top             =   840
      Width           =   735
   End
   Begin VB.Label coeficient 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   7
      Left            =   9840
      TabIndex        =   10
      Top             =   480
      Width           =   735
   End
   Begin VB.Label coeficient 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   6
      Left            =   8640
      TabIndex        =   9
      Top             =   480
      Width           =   735
   End
   Begin VB.Label coeficient 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   5
      Left            =   7440
      TabIndex        =   8
      Top             =   480
      Width           =   735
   End
   Begin VB.Label coeficient 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   4
      Left            =   6240
      TabIndex        =   7
      Top             =   480
      Width           =   735
   End
   Begin VB.Label coeficient 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   3
      Left            =   5040
      TabIndex        =   6
      Top             =   480
      Width           =   735
   End
   Begin VB.Label coeficient 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   2
      Left            =   3840
      TabIndex        =   5
      Top             =   480
      Width           =   735
   End
   Begin VB.Label coeficient 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   1
      Left            =   2640
      TabIndex        =   4
      Top             =   480
      Width           =   735
   End
   Begin VB.Label msg 
      Alignment       =   2  'Center
      Caption         =   "Label1"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   13.5
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   2040
      TabIndex        =   3
      Top             =   2280
      Visible         =   0   'False
      Width           =   7335
   End
   Begin VB.Label masca 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   0
      Left            =   1440
      TabIndex        =   2
      Top             =   1200
      Width           =   735
   End
   Begin VB.Label variabila 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   0
      Left            =   1440
      TabIndex        =   1
      Top             =   840
      Width           =   735
   End
   Begin VB.Label coeficient 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   0
      Left            =   1440
      TabIndex        =   0
      Top             =   480
      Width           =   735
   End
End
Attribute VB_Name = "simulare"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim pas_crt As Integer

Private Sub make_shuffle()
For i = 0 To 7
    Call shuffle(i)
Next i
Call shuffle_3

End Sub

Private Sub Command1_Click()
Call evaluate
End Sub

Private Sub Form_Load()
    Dim i As Byte
    pas_crt = 0
    For i = 0 To 7
        coeficient(i).Caption = coef_intr(i)
        variabila(i).Caption = Str(valoare)
        masca(i).Caption = i Mod 2
    Next i

End Sub

Private Sub shuffle(ByVal pas As Integer)
    If masca(pas).Caption = "1" Then
        coeficient(pas).Caption = Val(coeficient(pas).Caption) * Val(variabila(pas).Caption) * Val(masca(pas).Caption)
    End If
    variabila(pas).Caption = Str(Val(variabila(pas).Caption) * Val(variabila(pas).Caption))
End Sub

'0<= i <=n/2-1
Private Function shuffle_1(pas)
    If pas <= 8 \ 2 - 1 Then
        shuffle_1 = 2 * pas
    Else
        shuffle_1 = 2 * pas + 1 - 8
    End If
End Function

'transferul de la shuffle_1
Private Sub shuffle_3()
    Dim masca_tmp(0 To 7) As String
    
    For i = 0 To 7
        masca_tmp(shuffle_1(i)) = masca(i).Caption
    Next i
    For i = 0 To 7
        masca(i).Caption = masca_tmp(i)
    Next i
End Sub

Private Sub Form_Unload(Cancel As Integer)
    End
End Sub

Private Sub main_Timer()
    pas_crt = pas_crt + 1
    Call make_shuffle
    If pas_crt = 3 Then
        main.Enabled = False
        For i = 0 To 7
            variabila(i).Visible = False
            masca(i).Visible = False
        Next i
        Label3.Visible = False
        Label4.Visible = False
        pas_crt = 0
        second.Enabled = True
        Call ascunde_linii
    End If
End Sub

Private Sub evaluate()
    Dim coef_tmp(0 To 7) As Integer
    
    For i = 0 To 7 Step 2
        coef_tmp(i) = Val(coeficient(i \ 2).Caption) + Val(coeficient(i \ 2 + 4).Caption)
        coef_tmp(i + 1) = Val(coeficient(i \ 2).Caption) + Val(coeficient(i \ 2 + 4).Caption)
    Next i
    
    For i = 0 To 7
        coeficient(i).Caption = Trim(Str(coef_tmp(i)))
    Next i
End Sub

Private Sub second_Timer()
    
    
    
    second.Interval = 2500
    pas_crt = pas_crt + 1
    Call evaluate
    If pas_crt = 3 Then
        second.Enabled = False
        imagine.Visible = False
        msg.Visible = True
        msg.Caption = "Valoarea polinomului in punctul dat este: " + coeficient(0).Caption
    End If
End Sub

Private Sub ascunde_linii()
    Dim pas As Integer
    
    For pas = 0 To 39 Step 1
        linie(pas).Visible = False
    Next pas
    
    
    
    
End Sub

