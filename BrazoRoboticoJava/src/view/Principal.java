package view;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;
import com.panamahitek.PanamaHitek_Arduino;
import com.panamahitek.PanamaHitek_MultiMessage;
import com.panamahitek.ArduinoException;
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
import javax.swing.JOptionPane;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.logging.Level;
import java.util.logging.Logger;
import jssc.SerialPortEventListener;
import jssc.SerialPortEvent;
import jssc.SerialPortException;

public class Principal extends JFrame {

    //Declaración de variables para gestionar arduino
    PanamaHitek_Arduino arduino;
    PanamaHitek_MultiMessage multi;
    SerialPortEventListener listener;
    //Creación de componentes que se mostrarán en la vista
    Font wordType1, wordType2;
    Color backgroundBtn;
    ImageIcon iconLeft, iconRight, iconSend, iconAdd, iconDelete;
    Rectangle robotPieces, btnLeft, btnRight;
    //Componentes para los bontones que controlan la posición del robot
    JPanel pnlPrincipal, pnlPosition;

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
    JButton btnResume, btnSend, btnAdd, btnDelete;

    JLabel lblImgBackground;
    JLabel lblRoboticArm;

    ButtonController btnCtrl;

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

        listener = new SerialPortEventListener() {
            @Override
            public void serialEvent(SerialPortEvent spe) {
                try {
                    if (multi.dataReceptionCompleted()) {
                        //--------------------------------------------------------
                        // Estos print sopara ver que enviá el arduino
                        System.out.print("[UNO]: ");
                        System.out.println(multi.getMessage(0));
                        //--------------------------------------------------------

                        multi.flushBuffer();
                    }
                } catch (ArduinoException ex) {
                    Logger.getLogger(Principal.class.getName()).log(Level.SEVERE, null, ex);
                } catch (SerialPortException ex) {
                    Logger.getLogger(Principal.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        };

        btnCtrl = new ButtonController();
        //Establecer un tipo de letra para titulos
        wordType1 = new Font("", 1, 18);
        //Establecer un tipo de letra para etiquetas comunes
        wordType2 = new Font("", 0, 14);
        //Establecer un fondo para los JPanel que contienen los bótones
        backgroundBtn = new Color(190, 190, 190, 150);
        //Establecer el icono de añadir estado
        iconSend = new ImageIcon("src/image/right.png");
        //Establecer el icono de añadir estado
        iconAdd = new ImageIcon("src/image/add.png");
        //Establecer el icono de eliminar estado
        iconDelete = new ImageIcon("src/image/delete.png");
        //Establecer en que posición estará el botón izquierdo
        btnLeft = new Rectangle(10, 35, 40, 40);
        //Establecer en que posición estará el botón derecho
        btnRight = new Rectangle(80, 35, 40, 40);

        pnlPrincipal = new JPanel();
        pnlPrincipal.setLayout(null);
        lblRoboticArm = new JLabel("Panel de control de brazo robotico");
        lblRoboticArm.setFont(new Font("", 1, 18));
        lblRoboticArm.setBounds(20, 20, 450, 60);
        pnlPosition = new JPanel(null);
        pnlPosition.setBackground(backgroundBtn);
        pnlPosition.setBounds(50, 400, 280, 140);
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
        lblControl = new JLabel("Control");
        lblControl.setFont(wordType1);
        lblControl.setBounds(150, 70, 80, 30);
        rbtnAutomatic = new JRadioButton("Automatico");
        rbtnAutomatic.setFont(wordType2);
        rbtnAutomatic.setBounds(105, 110, 100, 20);
        rbtnAutomatic.addActionListener(btnCtrl);
        rbtnAutomatic.setSelected(true);
        rbtnManual = new JRadioButton("Manual");
        rbtnManual.setFont(wordType2);
        rbtnManual.setBounds(215, 110, 100, 20);
        rbtnManual.addActionListener(btnCtrl);
        groupRbtn = new ButtonGroup();
        groupRbtn.add(rbtnAutomatic);
        groupRbtn.add(rbtnManual);
        lblAutomation = new JLabel("Estados");

        lblAutomation.setFont(wordType1);
        lblAutomation.setBounds(150, 170, 140, 30);
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
        btnSend = new JButton(iconSend);
        btnSend.setBounds(80, 350, 40, 40);
        btnSend.addActionListener(btnCtrl);
        btnAdd = new JButton(iconAdd);
        btnAdd.setBounds(250, 350, 40, 40);
        btnAdd.addActionListener(btnCtrl);
        btnDelete = new JButton(iconDelete);
        btnDelete.setBounds(330, 350, 40, 40);
        btnDelete.addActionListener(btnCtrl);
        btnResume = new JButton("Reanudar");
        btnResume.setFont(wordType2);
        btnResume.addActionListener(btnCtrl);
        btnResume.setBounds(280, 560, 100, 30);
        lblImgBackground = new JLabel(new ImageIcon("src/images/imgBackground.jpg"));
        lblImgBackground.setBounds(400, 5, 230, 230);

        pnlPrincipal.setBounds(0, 0, 1150, 650);
    }

    public class ButtonController implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent e) {
            if (e.getSource() == btnAdd) {
                this.addStatus();
            } else if (e.getSource() == btnDelete) {
                this.deleteStatus();
            } else if (e.getSource() == btnSend) {

            } else if (e.getSource() == rbtnAutomatic) {
                sendArduinoInfo("A");
            } else if (e.getSource() == rbtnManual) {
                sendArduinoInfo("M");
            } else if (e.getSource() == btnResume) {
                sendArduinoInfo("R");
            }
        }

        private void deleteStatus() {
            sendArduinoInfo("D\n");
            for (int i = 0, e = tableAutomation.getRowCount(); i < e; i++) {
                dtmAutomation.removeRow(0);
            }
        }

        /** Verifica y añade un estado más al brazo */
        private void addStatus() {
            if (this.hasPositionValues()) {
                if (!this.validPosition()) {
                    JOptionPane.showMessageDialog(rootPane, "Los valores deben estar entre 0 y 180.");
                } else {
                    /* Enviamos un nuevo estado hacia arduino para que lo almacene*/
                    sendArduinoInfo("N\n");
                    /* Analizamos el valor del motor a pasos para quep pueda se guardado
                    en la memoria EEPROM de manera apropiada */
                    String foot = txtPosFoot.getText();
                    String sign = "1"; // Se envia uno sí es positivo
                    /* Sí el valor es negativo agregaremos el signo a parte*/
                    if (Integer.parseInt(foot) < 0) {
                        sign = "0";// Se envia 0 sí el valor del número es negativo
                        foot = foot.substring(1);
                    }
                    
                    /* Enviamos la información a arduino */
                    String newStatus = (
                            sign + toThreeChar(foot)
                            + toThreeChar(txtPosShoulder.getText())
                            + toThreeChar(txtPosElbow.getText())
                            + toThreeChar(txtPosWrist.getText())
                            + toThreeChar(txtPosHand.getText())
                    );
                    
                    sendArduinoInfo( newStatus );
                    System.out.println( newStatus );
                    /* Añadimos un nuevo renglon a nuestra interfaz*/
                    dtmAutomation.addRow(new Object[]{
                        tableAutomation.getRowCount() + 1,
                        txtPosFoot.getText(),
                        txtPosShoulder.getText(),
                        txtPosElbow.getText(),
                        txtPosWrist.getText(),
                        txtPosHand.getText()
                    });
                }

            } else {
                JOptionPane.showMessageDialog(rootPane, "Debes primero llenar todos los campos para guardar");
            }
        }

        private String toThreeChar(String txt) {
            return (txt.length() == 3) ? txt : (txt.length() == 1) ? "00" + txt : "0" + txt;
        }

        private boolean hasPositionValues() {
            return (!txtPosFoot.getText().equals(""))
                    && (!txtPosElbow.getText().equals(""))
                    && (!txtPosShoulder.getText().equals(""))
                    && (!txtPosWrist.getText().equals(""))
                    && (!txtPosHand.getText().equals(""));
        }

        private boolean validPosition() {
            return ((this.isAcceptable(txtPosElbow.getText()))
                    && (this.isAcceptable(txtPosShoulder.getText()))
                    && (this.isAcceptable(txtPosWrist.getText()))
                    && (this.isAcceptable(txtPosHand.getText())));
        }

        private boolean isAcceptable(String value) {
            int number = Integer.parseInt(value);
            return (number <= 180) && (number >= 0);
        }

    }

    //Método assemble, dónde se agregan todos los componentes a la vista
    private void assemble() {
        pnlPrincipal.add(lblRoboticArm);
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
        add(lblControl);
        add(rbtnAutomatic);
        add(rbtnManual);
        add(lblAutomation);
        add(scrollTable);
        add(btnSend);
        add(btnAdd);
        add(btnDelete);
        add(btnResume);
        pnlPrincipal.add(pnlPosition);

        pnlPrincipal.add(lblImgBackground);
        add(pnlPrincipal);
        try {
            arduino.arduinoRXTX("/dev/ttyACM0", 9600, listener);
        } catch (ArduinoException ex) {
            Logger.getLogger(Principal.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    private void sendArduinoInfo(String message) {
        try {
            arduino.sendData(message);
        } catch (Exception ex) {
            System.err.println("Error al tratar de enviar un mensaje");
            ex.printStackTrace();
        }
    }

    //Método launch5    5, es el que lanza la aplicación
    public void launch() {
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setSize(425, 650);
        this.setLocationRelativeTo(null);
        this.setResizable(false);
        this.setVisible(true);
    }

    public static void main(String[] args) {
        Principal p = new Principal();
        p.launch();
    }
}
