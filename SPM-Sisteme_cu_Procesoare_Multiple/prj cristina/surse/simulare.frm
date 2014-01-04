VERSION 5.00
Begin VB.Form simulare 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Simulare"
   ClientHeight    =   2340
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   8940
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2340
   ScaleWidth      =   8940
   StartUpPosition =   2  'CenterScreen
   Begin VB.Timer second 
      Enabled         =   0   'False
      Interval        =   6000
      Left            =   840
      Top             =   1560
   End
   Begin VB.Timer main 
      Interval        =   2500
      Left            =   240
      Top             =   1560
   End
   Begin VB.Image imagine 
      Height          =   900
      Left            =   1440
      Picture         =   "simulare.frx":0000
      Top             =   1320
      Width           =   7200
   End
   Begin VB.Label Label4 
      Alignment       =   1  'Right Justify
      Caption         =   "Masca:"
      Height          =   375
      Left            =   120
      TabIndex        =   27
      Top             =   960
      Width           =   975
   End
   Begin VB.Label Label3 
      Alignment       =   1  'Right Justify
      Caption         =   "Variabila:"
      Height          =   375
      Left            =   120
      TabIndex        =   26
      Top             =   600
      Width           =   975
   End
   Begin VB.Label Label2 
      Alignment       =   1  'Right Justify
      Caption         =   "Coeficient:"
      Height          =   375
      Left            =   120
      TabIndex        =   25
      Top             =   240
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
      Left            =   8040
      TabIndex        =   24
      Top             =   840
      Width           =   615
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
      Left            =   7080
      TabIndex        =   23
      Top             =   840
      Width           =   615
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
      Left            =   6120
      TabIndex        =   22
      Top             =   840
      Width           =   615
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
      Left            =   5160
      TabIndex        =   21
      Top             =   840
      Width           =   615
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
      Left            =   4200
      TabIndex        =   20
      Top             =   840
      Width           =   615
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
      Left            =   3240
      TabIndex        =   19
      Top             =   840
      Width           =   615
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
      Left            =   2280
      TabIndex        =   18
      Top             =   840
      Width           =   615
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
      Left            =   8040
      TabIndex        =   17
      Top             =   480
      Width           =   615
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
      Left            =   7080
      TabIndex        =   16
      Top             =   480
      Width           =   615
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
      Left            =   6120
      TabIndex        =   15
      Top             =   480
      Width           =   615
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
      Left            =   5160
      TabIndex        =   14
      Top             =   480
      Width           =   615
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
      Left            =   4200
      TabIndex        =   13
      Top             =   480
      Width           =   615
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
      Left            =   3240
      TabIndex        =   12
      Top             =   480
      Width           =   615
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
      Left            =   2280
      TabIndex        =   11
      Top             =   480
      Width           =   615
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
      Left            =   8040
      TabIndex        =   10
      Top             =   120
      Width           =   615
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
      Left            =   7080
      TabIndex        =   9
      Top             =   120
      Width           =   615
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
      Left            =   6120
      TabIndex        =   8
      Top             =   120
      Width           =   615
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
      Left            =   5160
      TabIndex        =   7
      Top             =   120
      Width           =   615
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
      Left            =   4200
      TabIndex        =   6
      Top             =   120
      Width           =   615
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
      Left            =   3240
      TabIndex        =   5
      Top             =   120
      Width           =   615
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
      Left            =   2280
      TabIndex        =   4
      Top             =   120
      Width           =   615
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
      Left            =   1440
      TabIndex        =   3
      Top             =   1560
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
      Left            =   1320
      TabIndex        =   2
      Top             =   840
      Width           =   615
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
      Left            =   1320
      TabIndex        =   1
      Top             =   480
      Width           =   615
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
      Left            =   1320
      TabIndex        =   0
      Top             =   120
      Width           =   615
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
