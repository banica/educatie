VERSION 5.00
Begin VB.Form principal 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Shuffle Exchange"
   ClientHeight    =   1785
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   10560
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1785
   ScaleWidth      =   10560
   StartUpPosition =   2  'CenterScreen
   Begin VB.TextBox val_x 
      Height          =   285
      Left            =   7920
      TabIndex        =   9
      Top             =   1320
      Width           =   495
   End
   Begin VB.CommandButton continua 
      Caption         =   "Simulare"
      Height          =   375
      Left            =   8760
      TabIndex        =   10
      Top             =   1320
      Width           =   1575
   End
   Begin VB.TextBox coeficienti 
      Height          =   285
      Index           =   7
      Left            =   9360
      TabIndex        =   8
      Top             =   840
      Width           =   735
   End
   Begin VB.TextBox coeficienti 
      Height          =   285
      Index           =   6
      Left            =   8040
      TabIndex        =   7
      Top             =   840
      Width           =   735
   End
   Begin VB.TextBox coeficienti 
      Height          =   285
      Index           =   5
      Left            =   6720
      TabIndex        =   6
      Top             =   840
      Width           =   735
   End
   Begin VB.TextBox coeficienti 
      Height          =   285
      Index           =   4
      Left            =   5400
      TabIndex        =   5
      Top             =   840
      Width           =   735
   End
   Begin VB.TextBox coeficienti 
      Height          =   285
      Index           =   3
      Left            =   4080
      TabIndex        =   4
      Top             =   840
      Width           =   735
   End
   Begin VB.TextBox coeficienti 
      Height          =   285
      Index           =   2
      Left            =   2760
      TabIndex        =   3
      Top             =   840
      Width           =   735
   End
   Begin VB.TextBox coeficienti 
      Height          =   285
      Index           =   1
      Left            =   1440
      TabIndex        =   2
      Top             =   840
      Width           =   735
   End
   Begin VB.TextBox coeficienti 
      Height          =   285
      Index           =   0
      Left            =   120
      TabIndex        =   1
      Top             =   840
      Width           =   735
   End
   Begin VB.Label Label3 
      Caption         =   "X="
      Height          =   255
      Left            =   7680
      TabIndex        =   19
      Top             =   1320
      Width           =   255
   End
   Begin VB.Label Label2 
      Caption         =   "x^7"
      Height          =   255
      Index           =   7
      Left            =   10200
      TabIndex        =   18
      Top             =   840
      Width           =   375
   End
   Begin VB.Label Label2 
      Caption         =   "x^6+"
      Height          =   255
      Index           =   6
      Left            =   8880
      TabIndex        =   17
      Top             =   840
      Width           =   375
   End
   Begin VB.Label Label2 
      Caption         =   "x^5+"
      Height          =   255
      Index           =   5
      Left            =   7560
      TabIndex        =   16
      Top             =   840
      Width           =   375
   End
   Begin VB.Label Label2 
      Caption         =   "x^4+"
      Height          =   255
      Index           =   4
      Left            =   6240
      TabIndex        =   15
      Top             =   840
      Width           =   375
   End
   Begin VB.Label Label2 
      Caption         =   "x^3+"
      Height          =   255
      Index           =   3
      Left            =   4920
      TabIndex        =   14
      Top             =   840
      Width           =   375
   End
   Begin VB.Label Label2 
      Caption         =   "x^2+"
      Height          =   255
      Index           =   2
      Left            =   3600
      TabIndex        =   13
      Top             =   840
      Width           =   375
   End
   Begin VB.Label Label2 
      Caption         =   "x^1+"
      Height          =   255
      Index           =   1
      Left            =   2280
      TabIndex        =   12
      Top             =   840
      Width           =   375
   End
   Begin VB.Label Label2 
      Caption         =   "x^0+"
      Height          =   255
      Index           =   0
      Left            =   960
      TabIndex        =   11
      Top             =   840
      Width           =   375
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      Caption         =   $"principal.frx":0000
      Height          =   495
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   10215
   End
End
Attribute VB_Name = "principal"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub continua_Click()
Dim ok As Boolean
Dim i As Byte

ok = True
For i = 0 To 7
    If (coeficienti(i).Text = "") Or (Not IsNumeric(coeficienti(i).Text)) Then
        ok = False
    Else
        coef_intr(i) = Int(coeficienti(i).Text)
    End If
Next i

If ok Then
    If (val_x.Text <> "") Or (Not IsNumeric(val_x.Text)) Then
        valoare = Val(val_x.Text)
    Else
        ok = False
    End If
End If
    
If ok Then
    Me.Visible = False
    simulare.Visible = True
    simulare.Show
Else
    MsgBox "Va rugam completati corect toti coeficientii!", vbOKOnly + vbExclamation, "Eroare"
End If
End Sub

