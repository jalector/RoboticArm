package View;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;
import com.panamahitek.PanamaHitek_Arduino;
import com.panamahitek.PanamaHitek_MultiMessage;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Font;
import java.awt.Rectangle;
import javax.swing.ButtonGroup;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JRadioButton;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.UIManager;
import javax.swing.table.DefaultTableModel;
import jssc.SerialPortEventListener;

public class Principal extends JFrame {

    //Declaración de variables para gestionar arduino
    PanamaHitek_Arduino arduino;
    PanamaHitek_MultiMessage multi;
    SerialPortEventListener listener;
    //Creación de componentes que se mostrarán en la vista
    Font wordType1, wordType2;
    Color backgroundBtn;
    ImageIcon iconLeft, iconRight, iconAdd, iconDelete;
    Rectangle robotPieces, btnLeft, btnRight;
    //Componentes para los bontones que controlan la posición del robot
    JPanel pnlPrincipal, pnlFoot, pnlShoulder, pnlElbow, pnlWrist, pnlHand, pnlPosition, pnlControl;
    JLabel lblFoot, lblShoulder, lblElbow, lblWrist, lblHand;
    JButton btnLeftFoot, btnRightFoot, btnLeftShoulder, btnRightShoulder, btnLeftElbow, btnRightElbow,
            btnLeftWrist, btnRightWrist, btnLeftHand, btnRightHand;
    //Componentes que muestran información sobre las instrucciones que se le darán al robot
    JLabel lblPosition, lblPosFoot, lblPosShoulder, lblPosElbow, lblPosWrist, lblPosHand;
    JTextField txtPosFoot, txtPosShoulder, txtPosElbow, txtPosWrist, txtPosHand;
    //Componentes que controlan
    JLabel lblControl, lblAutomation;
    JRadioButton rbtnAutomatic, rbtnManual;
    ButtonGroup groupRbtn;
    JTable tableAutomation;
    DefaultTableModel dtmAutomation;
    JScrollPane scrollTable;
    String colTable[] = {"Orden", "Base", "Hombro", "Codo", "Muñeca", "Mano"};
    JButton btnAbort, btnResume, btnAdd, btnDelete;

    JLabel lblImgBackground;
    JLabel lblRoboticArm;

    //Creación del constructor de la clase
    Principal() {
        super("Brazo robotico");
        lookAndFell();
        create();
        assemble();
    }//Método lookAndFell, Sirve para darle un diseño más agradable a la aplicación

    public void lookAndFell() {
        try {
            UIManager.setLookAndFeel("com.sun.java.swing.plaf.nimbus.NimbusLookAndFeel");
        } catch (ClassNotFoundException | InstantiationException | IllegalAccessException
                | javax.swing.UnsupportedLookAndFeelException ex) {
        }
    }

    //Método create, dónde se inicializan todas las variables
    private void create() {
        arduino = new PanamaHitek_Arduino();
        multi = new PanamaHitek_MultiMessage(1, arduino);
        //Establecer un tipo de letra para titulos
        wordType1 = new Font("", 1, 18);
        //Establecer un tipo de letra para etiquetas comunes
        wordType2 = new Font("", 0, 14);
        //Establecer un fondo para los JPanel que contienen los bótones
        backgroundBtn = new Color(190, 190, 190, 150);
        //Establecer el icono de la flecha izquierda
        iconLeft = new ImageIcon("src/image/left.png");
        //Establecer el icono de la flecha derecha
        iconRight = new ImageIcon("src/image/right.png");
        //Establecer el icono de añadir estado
        iconAdd = new ImageIcon("src/image/add.png");
        //Establecer el icono de eliminar estado
        iconDelete = new ImageIcon("src/image/delete.png");
        //Establecer en que posición estará el titulo de cada parte del robot
        robotPieces = new Rectangle(30, 5, 140, 30);
        //Establecer en que posición estará el botón izquierdo
        btnLeft = new Rectangle(10, 35, 40, 40);
        //Establecer en que posición estará el botón derecho
        btnRight = new Rectangle(80, 35, 40, 40);

        pnlPrincipal = new JPanel();
        pnlPrincipal.setLayout(null);
        lblRoboticArm = new JLabel("Panel de control de brazo robotico");
        lblRoboticArm.setFont(new Font("", 1, 25));
        lblRoboticArm.setBounds(140, 20, 450, 60);
        pnlFoot = new JPanel(null);
        pnlFoot.setBackground(backgroundBtn);
        pnlFoot.setBounds(100, 100, 130, 80);
        lblFoot = new JLabel("Base");
        lblFoot.setFont(wordType1);
        lblFoot.setBounds(robotPieces);
        btnLeftFoot = new JButton(iconLeft);
        btnLeftFoot.setBounds(btnLeft);
        btnRightFoot = new JButton(iconRight);
        btnRightFoot.setBounds(btnRight);

        pnlShoulder = new JPanel(null);
        pnlShoulder.setBackground(backgroundBtn);
        pnlShoulder.setBounds(100, 200, 130, 80);
        lblShoulder = new JLabel("Hombro");
        lblShoulder.setFont(wordType1);
        lblShoulder.setBounds(robotPieces);
        btnLeftShoulder = new JButton(iconLeft);
        btnLeftShoulder.setBounds(btnLeft);
        btnRightShoulder = new JButton(iconRight);
        btnRightShoulder.setBounds(btnRight);

        pnlElbow = new JPanel(null);
        pnlElbow.setBackground(backgroundBtn);
        pnlElbow.setBounds(100, 300, 130, 80);
        lblElbow = new JLabel("Codo");
        lblElbow.setFont(wordType1);
        lblElbow.setBounds(robotPieces);
        btnLeftElbow = new JButton(iconLeft);
        btnLeftElbow.setBounds(btnLeft);
        btnRightElbow = new JButton(iconRight);
        btnRightElbow.setBounds(btnRight);

        pnlWrist = new JPanel(null);
        pnlWrist.setBackground(backgroundBtn);
        pnlWrist.setBounds(100, 400, 130, 80);
        lblWrist = new JLabel("Muñeca");
        lblWrist.setFont(wordType1);
        lblWrist.setBounds(robotPieces);
        btnLeftWrist = new JButton(iconLeft);
        btnLeftWrist.setBounds(btnLeft);
        btnRightWrist = new JButton(iconRight);
        btnRightWrist.setBounds(btnRight);

        pnlHand = new JPanel(null);
        pnlHand.setBackground(backgroundBtn);
        pnlHand.setBounds(100, 500, 130, 80);
        lblHand = new JLabel("Mano");
        lblHand.setFont(wordType1);
        lblHand.setBounds(robotPieces);
        btnLeftHand = new JButton(iconLeft);
        btnLeftHand.setBounds(btnLeft);
        btnRightHand = new JButton(iconRight);
        btnRightHand.setBounds(btnRight);

        pnlPosition = new JPanel(null);
        pnlPosition.setBackground(backgroundBtn);
        pnlPosition.setBounds(400, 400, 280, 140);
        lblPosition = new JLabel("Posición");
        lblPosition.setFont(wordType1);
        lblPosition.setBounds(5, 5, 140, 30);
        lblPosFoot = new JLabel("Base");
        lblPosFoot.setFont(wordType2);
        lblPosFoot.setBounds(5, 40, 40, 20);
        txtPosFoot = new JTextField();
        txtPosFoot.setBounds(70, 35, 50, 30);
        lblPosShoulder = new JLabel("Hombro");
        lblPosShoulder.setFont(wordType2);
        lblPosShoulder.setBounds(5, 70, 70, 20);
        txtPosShoulder = new JTextField();
        txtPosShoulder.setBounds(70, 65, 50, 30);
        lblPosElbow = new JLabel("Codo");
        lblPosElbow.setFont(wordType2);
        lblPosElbow.setBounds(5, 100, 70, 20);
        txtPosElbow = new JTextField();
        txtPosElbow.setBounds(70, 95, 50, 30);
        lblPosWrist = new JLabel("Muñeca");
        lblPosWrist.setFont(wordType2);
        lblPosWrist.setBounds(140, 40, 70, 20);
        txtPosWrist = new JTextField();
        txtPosWrist.setBounds(205, 35, 50, 30);
        lblPosHand = new JLabel("Mano");
        lblPosHand.setFont(wordType2);
        lblPosHand.setBounds(140, 70, 70, 20);
        txtPosHand = new JTextField();
        txtPosHand.setBounds(205, 65, 50, 30);

        //Inicialización de los elementos que se encuentran dentro del panel de control
        pnlControl = new JPanel(null);
        pnlControl.setBackground(backgroundBtn);
        pnlControl.setBounds(750, 0, 400, 650);
        lblControl = new JLabel("Control");
        lblControl.setFont(wordType1);
        lblControl.setBounds(170, 70, 80, 30);
        rbtnAutomatic = new JRadioButton("Automatico");
        rbtnAutomatic.setFont(wordType2);
        rbtnAutomatic.setBounds(105, 110, 100, 20);
        rbtnManual = new JRadioButton("Manual");
        rbtnManual.setFont(wordType2);
        rbtnManual.setBounds(215, 110, 100, 20);
        groupRbtn = new ButtonGroup();
        groupRbtn.add(rbtnAutomatic);
        groupRbtn.add(rbtnManual);
        lblAutomation = new JLabel("Automatización");
        lblAutomation.setFont(wordType1);
        lblAutomation.setBounds(135, 170, 140, 30);
        dtmAutomation = new DefaultTableModel(null, colTable) {
            @Override
            public boolean isCellEditable(int fila, int columna) {
                return false;
            }
        };
        tableAutomation = new JTable(dtmAutomation);
        tableAutomation.getTableHeader().setReorderingAllowed(false);
        scrollTable = new JScrollPane(tableAutomation);
        scrollTable.setBounds(10, 210, 380, 120);
        btnAdd = new JButton(iconAdd);
        btnAdd.setBounds(250, 350, 40, 40);
        btnDelete = new JButton(iconDelete);
        btnDelete.setBounds(330, 350, 40, 40);
        btnAbort = new JButton("Abortar");
        btnAbort.setFont(wordType2);
        btnAbort.setBounds(20, 500, 100, 30);
        btnResume = new JButton("Reanudar");
        btnResume.setFont(wordType2);
        btnResume.setBounds(280, 500, 100, 30);
        lblImgBackground = new JLabel(new ImageIcon("src/images/imgBackground.jpg"));
        lblImgBackground.setBounds(400, 5, 230, 230);

        pnlPrincipal.setBounds(0, 0, 1150, 650);
    }

    //Método assemble, dónde se agregan todos los componentes a la vista
    private void assemble() {

        pnlPrincipal.add(lblRoboticArm);

        pnlFoot.add(lblFoot);
        pnlFoot.add(btnLeftFoot);
        pnlFoot.add(btnRightFoot);
        pnlShoulder.add(lblShoulder);
        pnlShoulder.add(btnLeftShoulder);
        pnlShoulder.add(btnRightShoulder);
        pnlElbow.add(lblElbow);
        pnlElbow.add(btnLeftElbow);
        pnlElbow.add(btnRightElbow);
        pnlWrist.add(lblWrist);
        pnlWrist.add(btnLeftWrist);
        pnlWrist.add(btnRightWrist);
        pnlHand.add(lblHand);
        pnlHand.add(btnLeftHand);
        pnlHand.add(btnRightHand);
        pnlPosition.add(lblPosition);
        pnlPosition.add(lblPosFoot);
        pnlPosition.add(txtPosFoot);
        pnlPosition.add(lblPosShoulder);
        pnlPosition.add(txtPosShoulder);
        pnlPosition.add(lblPosElbow);
        pnlPosition.add(txtPosElbow);
        pnlPosition.add(lblPosWrist);
        pnlPosition.add(txtPosWrist);
        pnlPosition.add(lblPosHand);
        pnlPosition.add(txtPosHand);
        pnlControl.add(lblControl);
        pnlControl.add(rbtnAutomatic);
        pnlControl.add(rbtnManual);
        pnlControl.add(lblAutomation);
        pnlControl.add(scrollTable);
        pnlControl.add(btnAdd);
        pnlControl.add(btnDelete);
        pnlControl.add(btnAbort);
        pnlControl.add(btnResume);
        pnlPrincipal.add(pnlFoot);
        pnlPrincipal.add(pnlShoulder);
        pnlPrincipal.add(pnlElbow);
        pnlPrincipal.add(pnlWrist);
        pnlPrincipal.add(pnlHand);
        pnlPrincipal.add(pnlPosition);
        pnlPrincipal.add(pnlControl);
        pnlPrincipal.add(lblImgBackground);
        add(pnlPrincipal);
//        try {
//            arduino.arduinoRXTX("COM7", 9600, listener);
//            //arduino.arduinoRXTX("/dev/ttyUSB0", 9600, listener);
//        } catch (ArduinoException ex) {
//            Logger.getLogger(Principal.class.getName()).log(Level.SEVERE, null, ex);
//        }
    }

    //Método launch, es el que lanza la aplicación
    public void launch() {
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(1150, 650);
        setVisible(true);
        this.setResizable(false);
    }

    public static void main(String[] args) {
        Principal p = new Principal();
        p.launch();
    }
}
