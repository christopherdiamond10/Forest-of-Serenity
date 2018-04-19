namespace AnimationEditor
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.AnimationPanel = new System.Windows.Forms.Panel();
            this.AnimationFrames_Listview = new System.Windows.Forms.ListView();
            this.columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.button2 = new System.Windows.Forms.Button();
            this.Heal3_Button = new System.Windows.Forms.Button();
            this.Fire1_Button = new System.Windows.Forms.Button();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.AnimationPicture_UVCoords_Panel = new System.Windows.Forms.Panel();
            this.Add_Frame_Button = new System.Windows.Forms.Button();
            this.Remove_Frame_Button = new System.Windows.Forms.Button();
            this.Copy_Frame_Button = new System.Windows.Forms.Button();
            this.Clear_Frame_Button = new System.Windows.Forms.Button();
            this.Paste_Frame_Button = new System.Windows.Forms.Button();
            this.MouseCoords_TextBox = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.TextureHeight_NumericUpDown = new System.Windows.Forms.NumericUpDown();
            this.TextureWidth_NumericUpDown = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.Remove_Sprite_Button = new System.Windows.Forms.Button();
            this.Add_Sprite_Button = new System.Windows.Forms.Button();
            this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);
            this.Relative_to_Screen_Checkbox = new System.Windows.Forms.CheckBox();
            this.Animation_Partially_Completed_CheckBox = new System.Windows.Forms.CheckBox();
            this.Sounds_ComboBox = new System.Windows.Forms.ComboBox();
            this.Tint_screen_Checkbox = new System.Windows.Forms.CheckBox();
            this.PlayAnimation_Button = new System.Windows.Forms.Button();
            this.WaitTime_NumericUpDown = new System.Windows.Forms.NumericUpDown();
            this.SwapSprite_Button = new System.Windows.Forms.Button();
            this.TintCharacter_CheckBox = new System.Windows.Forms.CheckBox();
            this.Play_Sound_Button = new System.Windows.Forms.Button();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.TintScreenRed_numericUpDown = new System.Windows.Forms.NumericUpDown();
            this.TintScreenGreen_numericUpDown = new System.Windows.Forms.NumericUpDown();
            this.TintScreenBlue_numericUpDown = new System.Windows.Forms.NumericUpDown();
            this.TintScreenAlpha_numericUpDown = new System.Windows.Forms.NumericUpDown();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.OpenFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.TintCharacterBlue_NumericUpDown = new System.Windows.Forms.NumericUpDown();
            this.TintCharacterGreen_NumericUpDown = new System.Windows.Forms.NumericUpDown();
            this.TintCharacterRed_NumericUpDown = new System.Windows.Forms.NumericUpDown();
            this.label10 = new System.Windows.Forms.Label();
            this.Zoom_NumericUpDown1 = new System.Windows.Forms.NumericUpDown();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.TextureHeight_NumericUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.TextureWidth_NumericUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.WaitTime_NumericUpDown)).BeginInit();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.TintScreenRed_numericUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.TintScreenGreen_numericUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.TintScreenBlue_numericUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.TintScreenAlpha_numericUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.TintCharacterBlue_NumericUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.TintCharacterGreen_NumericUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.TintCharacterRed_NumericUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Zoom_NumericUpDown1)).BeginInit();
            this.SuspendLayout();
            // 
            // AnimationPanel
            // 
            this.AnimationPanel.BackColor = System.Drawing.Color.DarkSlateBlue;
            this.AnimationPanel.Location = new System.Drawing.Point(98, 288);
            this.AnimationPanel.Name = "AnimationPanel";
            this.AnimationPanel.Size = new System.Drawing.Size(715, 489);
            this.AnimationPanel.TabIndex = 0;
            this.AnimationPanel.Paint += new System.Windows.Forms.PaintEventHandler(this.AnimationPanel_Paint);
            this.AnimationPanel.MouseClick += new System.Windows.Forms.MouseEventHandler(this.AnimationPanel_MouseClick);
            this.AnimationPanel.MouseDown += new System.Windows.Forms.MouseEventHandler(this.AnimationPanel_MouseDown);
            this.AnimationPanel.MouseMove += new System.Windows.Forms.MouseEventHandler(this.AnimationPanel_MouseMove);
            this.AnimationPanel.MouseUp += new System.Windows.Forms.MouseEventHandler(this.AnimationPanel_MouseUp);
            // 
            // AnimationFrames_Listview
            // 
            this.AnimationFrames_Listview.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1});
            this.AnimationFrames_Listview.Location = new System.Drawing.Point(14, 288);
            this.AnimationFrames_Listview.MultiSelect = false;
            this.AnimationFrames_Listview.Name = "AnimationFrames_Listview";
            this.AnimationFrames_Listview.Size = new System.Drawing.Size(78, 270);
            this.AnimationFrames_Listview.TabIndex = 1;
            this.toolTip1.SetToolTip(this.AnimationFrames_Listview, "Select Frames to Switch to");
            this.AnimationFrames_Listview.UseCompatibleStateImageBehavior = false;
            this.AnimationFrames_Listview.View = System.Windows.Forms.View.SmallIcon;
            this.AnimationFrames_Listview.SelectedIndexChanged += new System.EventHandler(this.AnimationFrames_Listview_SelectedIndexChanged);
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Location = new System.Drawing.Point(819, 288);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(243, 489);
            this.tabControl1.TabIndex = 2;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.button2);
            this.tabPage1.Controls.Add(this.Heal3_Button);
            this.tabPage1.Controls.Add(this.Fire1_Button);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(235, 463);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "tabPage1";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // button2
            // 
            this.button2.Image = ((System.Drawing.Image)(resources.GetObject("button2.Image")));
            this.button2.Location = new System.Drawing.Point(127, 7);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(54, 53);
            this.button2.TabIndex = 2;
            this.button2.UseVisualStyleBackColor = true;
            // 
            // Heal3_Button
            // 
            this.Heal3_Button.Image = ((System.Drawing.Image)(resources.GetObject("Heal3_Button.Image")));
            this.Heal3_Button.Location = new System.Drawing.Point(67, 7);
            this.Heal3_Button.Name = "Heal3_Button";
            this.Heal3_Button.Size = new System.Drawing.Size(54, 53);
            this.Heal3_Button.TabIndex = 1;
            this.Heal3_Button.UseVisualStyleBackColor = true;
            this.Heal3_Button.Click += new System.EventHandler(this.Heal3_Button_Click);
            // 
            // Fire1_Button
            // 
            this.Fire1_Button.Image = ((System.Drawing.Image)(resources.GetObject("Fire1_Button.Image")));
            this.Fire1_Button.Location = new System.Drawing.Point(7, 7);
            this.Fire1_Button.Name = "Fire1_Button";
            this.Fire1_Button.Size = new System.Drawing.Size(54, 53);
            this.Fire1_Button.TabIndex = 0;
            this.Fire1_Button.UseVisualStyleBackColor = true;
            this.Fire1_Button.Click += new System.EventHandler(this.Fire1_Button_Click);
            // 
            // tabPage2
            // 
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(235, 463);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "tabPage2";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // AnimationPicture_UVCoords_Panel
            // 
            this.AnimationPicture_UVCoords_Panel.BackColor = System.Drawing.SystemColors.ActiveBorder;
            this.AnimationPicture_UVCoords_Panel.Location = new System.Drawing.Point(98, 55);
            this.AnimationPicture_UVCoords_Panel.Name = "AnimationPicture_UVCoords_Panel";
            this.AnimationPicture_UVCoords_Panel.Size = new System.Drawing.Size(666, 227);
            this.AnimationPicture_UVCoords_Panel.TabIndex = 3;
            this.AnimationPicture_UVCoords_Panel.Paint += new System.Windows.Forms.PaintEventHandler(this.AnimationPicture_UVCoords_Panel_Paint);
            this.AnimationPicture_UVCoords_Panel.MouseClick += new System.Windows.Forms.MouseEventHandler(this.AnimationPicture_UVCoords_Panel_MouseClick);
            this.AnimationPicture_UVCoords_Panel.MouseMove += new System.Windows.Forms.MouseEventHandler(this.AnimationPicture_UVCoords_Panel_MouseMove);
            // 
            // Add_Frame_Button
            // 
            this.Add_Frame_Button.Location = new System.Drawing.Point(14, 564);
            this.Add_Frame_Button.Name = "Add_Frame_Button";
            this.Add_Frame_Button.Size = new System.Drawing.Size(75, 37);
            this.Add_Frame_Button.TabIndex = 4;
            this.Add_Frame_Button.Text = "Add Frame";
            this.Add_Frame_Button.UseVisualStyleBackColor = true;
            this.Add_Frame_Button.Click += new System.EventHandler(this.Add_Frame_Button_Click);
            // 
            // Remove_Frame_Button
            // 
            this.Remove_Frame_Button.Location = new System.Drawing.Point(14, 607);
            this.Remove_Frame_Button.Name = "Remove_Frame_Button";
            this.Remove_Frame_Button.Size = new System.Drawing.Size(75, 37);
            this.Remove_Frame_Button.TabIndex = 5;
            this.Remove_Frame_Button.Text = "Remove Frame";
            this.Remove_Frame_Button.UseVisualStyleBackColor = true;
            this.Remove_Frame_Button.Click += new System.EventHandler(this.Remove_Frame_Button_Click);
            // 
            // Copy_Frame_Button
            // 
            this.Copy_Frame_Button.Location = new System.Drawing.Point(14, 650);
            this.Copy_Frame_Button.Name = "Copy_Frame_Button";
            this.Copy_Frame_Button.Size = new System.Drawing.Size(75, 37);
            this.Copy_Frame_Button.TabIndex = 6;
            this.Copy_Frame_Button.Text = "Copy Frame";
            this.Copy_Frame_Button.UseVisualStyleBackColor = true;
            this.Copy_Frame_Button.Click += new System.EventHandler(this.Copy_Frame_Button_Click);
            // 
            // Clear_Frame_Button
            // 
            this.Clear_Frame_Button.Location = new System.Drawing.Point(14, 736);
            this.Clear_Frame_Button.Name = "Clear_Frame_Button";
            this.Clear_Frame_Button.Size = new System.Drawing.Size(75, 37);
            this.Clear_Frame_Button.TabIndex = 7;
            this.Clear_Frame_Button.Text = "Clear Frame";
            this.Clear_Frame_Button.UseVisualStyleBackColor = true;
            this.Clear_Frame_Button.Click += new System.EventHandler(this.Clear_Frame_Button_Click);
            // 
            // Paste_Frame_Button
            // 
            this.Paste_Frame_Button.Location = new System.Drawing.Point(14, 693);
            this.Paste_Frame_Button.Name = "Paste_Frame_Button";
            this.Paste_Frame_Button.Size = new System.Drawing.Size(75, 37);
            this.Paste_Frame_Button.TabIndex = 8;
            this.Paste_Frame_Button.Text = "Paste Frame";
            this.Paste_Frame_Button.UseVisualStyleBackColor = true;
            this.Paste_Frame_Button.Click += new System.EventHandler(this.Paste_Frame_Button_Click);
            // 
            // MouseCoords_TextBox
            // 
            this.MouseCoords_TextBox.Location = new System.Drawing.Point(14, 262);
            this.MouseCoords_TextBox.Name = "MouseCoords_TextBox";
            this.MouseCoords_TextBox.ReadOnly = true;
            this.MouseCoords_TextBox.Size = new System.Drawing.Size(78, 20);
            this.MouseCoords_TextBox.TabIndex = 9;
            this.toolTip1.SetToolTip(this.MouseCoords_TextBox, "Mouse Coordinates");
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(-3, 244);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(99, 15);
            this.label1.TabIndex = 10;
            this.label1.Text = "Mouse Coords";
            // 
            // TextureHeight_NumericUpDown
            // 
            this.TextureHeight_NumericUpDown.Location = new System.Drawing.Point(771, 262);
            this.TextureHeight_NumericUpDown.Maximum = new decimal(new int[] {
            768,
            0,
            0,
            0});
            this.TextureHeight_NumericUpDown.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.TextureHeight_NumericUpDown.Name = "TextureHeight_NumericUpDown";
            this.TextureHeight_NumericUpDown.Size = new System.Drawing.Size(49, 20);
            this.TextureHeight_NumericUpDown.TabIndex = 11;
            this.TextureHeight_NumericUpDown.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.TextureHeight_NumericUpDown.ValueChanged += new System.EventHandler(this.TextureHeight_NumericUpDown_ValueChanged);
            // 
            // TextureWidth_NumericUpDown
            // 
            this.TextureWidth_NumericUpDown.Location = new System.Drawing.Point(771, 236);
            this.TextureWidth_NumericUpDown.Maximum = new decimal(new int[] {
            1028,
            0,
            0,
            0});
            this.TextureWidth_NumericUpDown.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.TextureWidth_NumericUpDown.Name = "TextureWidth_NumericUpDown";
            this.TextureWidth_NumericUpDown.Size = new System.Drawing.Size(49, 20);
            this.TextureWidth_NumericUpDown.TabIndex = 12;
            this.TextureWidth_NumericUpDown.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.TextureWidth_NumericUpDown.ValueChanged += new System.EventHandler(this.TextureWidth_NumericUpDown_ValueChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(782, 218);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(87, 15);
            this.label2.TabIndex = 13;
            this.label2.Text = "Texture Size";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(826, 236);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(43, 15);
            this.label3.TabIndex = 14;
            this.label3.Text = "Width";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(826, 262);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(49, 15);
            this.label4.TabIndex = 15;
            this.label4.Text = "Height";
            // 
            // Remove_Sprite_Button
            // 
            this.Remove_Sprite_Button.Location = new System.Drawing.Point(14, 189);
            this.Remove_Sprite_Button.Name = "Remove_Sprite_Button";
            this.Remove_Sprite_Button.Size = new System.Drawing.Size(75, 46);
            this.Remove_Sprite_Button.TabIndex = 16;
            this.Remove_Sprite_Button.Text = "Remove Sprite";
            this.toolTip1.SetToolTip(this.Remove_Sprite_Button, "Changes States to allow you to Remove any Selected Sprites");
            this.Remove_Sprite_Button.UseVisualStyleBackColor = true;
            this.Remove_Sprite_Button.Click += new System.EventHandler(this.Remove_Sprite_Button_Click);
            // 
            // Add_Sprite_Button
            // 
            this.Add_Sprite_Button.Location = new System.Drawing.Point(14, 89);
            this.Add_Sprite_Button.Name = "Add_Sprite_Button";
            this.Add_Sprite_Button.Size = new System.Drawing.Size(75, 46);
            this.Add_Sprite_Button.TabIndex = 17;
            this.Add_Sprite_Button.Text = "Add Sprite";
            this.toolTip1.SetToolTip(this.Add_Sprite_Button, "Changes States to allow you to Add Sprites from the Picture Panel");
            this.Add_Sprite_Button.UseVisualStyleBackColor = true;
            this.Add_Sprite_Button.Click += new System.EventHandler(this.Add_Sprite_Button_Click);
            // 
            // Relative_to_Screen_Checkbox
            // 
            this.Relative_to_Screen_Checkbox.AutoSize = true;
            this.Relative_to_Screen_Checkbox.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Relative_to_Screen_Checkbox.Location = new System.Drawing.Point(881, 239);
            this.Relative_to_Screen_Checkbox.Name = "Relative_to_Screen_Checkbox";
            this.Relative_to_Screen_Checkbox.Size = new System.Drawing.Size(136, 17);
            this.Relative_to_Screen_Checkbox.TabIndex = 18;
            this.Relative_to_Screen_Checkbox.Text = "Relative To Screen";
            this.toolTip1.SetToolTip(this.Relative_to_Screen_Checkbox, "Sprite Sizes Change if animation is relative to the screen and positions of sprit" +
                    "e in game do not revolve around an objects position");
            this.Relative_to_Screen_Checkbox.UseVisualStyleBackColor = true;
            // 
            // Animation_Partially_Completed_CheckBox
            // 
            this.Animation_Partially_Completed_CheckBox.AutoSize = true;
            this.Animation_Partially_Completed_CheckBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Animation_Partially_Completed_CheckBox.Location = new System.Drawing.Point(881, 263);
            this.Animation_Partially_Completed_CheckBox.Name = "Animation_Partially_Completed_CheckBox";
            this.Animation_Partially_Completed_CheckBox.Size = new System.Drawing.Size(193, 17);
            this.Animation_Partially_Completed_CheckBox.TabIndex = 19;
            this.Animation_Partially_Completed_CheckBox.Text = "Animation Partially Completed";
            this.toolTip1.SetToolTip(this.Animation_Partially_Completed_CheckBox, "Until an Animation is at least partially completed, all participants involved wit" +
                    "h the animation cannot move");
            this.Animation_Partially_Completed_CheckBox.UseVisualStyleBackColor = true;
            this.Animation_Partially_Completed_CheckBox.CheckedChanged += new System.EventHandler(this.Animation_Partially_Completed_CheckBox_CheckedChanged);
            // 
            // Sounds_ComboBox
            // 
            this.Sounds_ComboBox.FormattingEnabled = true;
            this.Sounds_ComboBox.Location = new System.Drawing.Point(939, 189);
            this.Sounds_ComboBox.Name = "Sounds_ComboBox";
            this.Sounds_ComboBox.Size = new System.Drawing.Size(106, 21);
            this.Sounds_ComboBox.TabIndex = 20;
            this.toolTip1.SetToolTip(this.Sounds_ComboBox, resources.GetString("Sounds_ComboBox.ToolTip"));
            this.Sounds_ComboBox.SelectedIndexChanged += new System.EventHandler(this.Sounds_ComboBox_SelectedIndexChanged);
            // 
            // Tint_screen_Checkbox
            // 
            this.Tint_screen_Checkbox.AutoSize = true;
            this.Tint_screen_Checkbox.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Tint_screen_Checkbox.Location = new System.Drawing.Point(950, 34);
            this.Tint_screen_Checkbox.Name = "Tint_screen_Checkbox";
            this.Tint_screen_Checkbox.Size = new System.Drawing.Size(99, 17);
            this.Tint_screen_Checkbox.TabIndex = 23;
            this.Tint_screen_Checkbox.Text = "Tint Screen?";
            this.toolTip1.SetToolTip(this.Tint_screen_Checkbox, "Tint Screen?");
            this.Tint_screen_Checkbox.UseVisualStyleBackColor = true;
            this.Tint_screen_Checkbox.CheckedChanged += new System.EventHandler(this.Tint_screen_Checkbox_CheckedChanged);
            // 
            // PlayAnimation_Button
            // 
            this.PlayAnimation_Button.Image = ((System.Drawing.Image)(resources.GetObject("PlayAnimation_Button.Image")));
            this.PlayAnimation_Button.Location = new System.Drawing.Point(14, 34);
            this.PlayAnimation_Button.Name = "PlayAnimation_Button";
            this.PlayAnimation_Button.Size = new System.Drawing.Size(75, 49);
            this.PlayAnimation_Button.TabIndex = 29;
            this.toolTip1.SetToolTip(this.PlayAnimation_Button, "Play Animation");
            this.PlayAnimation_Button.UseVisualStyleBackColor = true;
            this.PlayAnimation_Button.Click += new System.EventHandler(this.PlayAnimation_Button_Click);
            // 
            // WaitTime_NumericUpDown
            // 
            this.WaitTime_NumericUpDown.Increment = new decimal(new int[] {
            5,
            0,
            0,
            0});
            this.WaitTime_NumericUpDown.Location = new System.Drawing.Point(770, 178);
            this.WaitTime_NumericUpDown.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.WaitTime_NumericUpDown.Minimum = new decimal(new int[] {
            20,
            0,
            0,
            0});
            this.WaitTime_NumericUpDown.Name = "WaitTime_NumericUpDown";
            this.WaitTime_NumericUpDown.Size = new System.Drawing.Size(56, 20);
            this.WaitTime_NumericUpDown.TabIndex = 30;
            this.toolTip1.SetToolTip(this.WaitTime_NumericUpDown, "Wait Timer between this frame and the next frame, these are milliseconds");
            this.WaitTime_NumericUpDown.Value = new decimal(new int[] {
            40,
            0,
            0,
            0});
            this.WaitTime_NumericUpDown.ValueChanged += new System.EventHandler(this.WaitTime_NumericUpDown_ValueChanged);
            // 
            // SwapSprite_Button
            // 
            this.SwapSprite_Button.Location = new System.Drawing.Point(14, 137);
            this.SwapSprite_Button.Name = "SwapSprite_Button";
            this.SwapSprite_Button.Size = new System.Drawing.Size(75, 46);
            this.SwapSprite_Button.TabIndex = 32;
            this.SwapSprite_Button.Text = "Swap Sprite";
            this.toolTip1.SetToolTip(this.SwapSprite_Button, "Swaps the Currently Selected Sprite With the Texture and Bitmap Currently highlig" +
                    "hted in the Picture Panel.");
            this.SwapSprite_Button.UseVisualStyleBackColor = true;
            this.SwapSprite_Button.Click += new System.EventHandler(this.SwapSprite_Button_Click);
            // 
            // TintCharacter_CheckBox
            // 
            this.TintCharacter_CheckBox.AutoSize = true;
            this.TintCharacter_CheckBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TintCharacter_CheckBox.Location = new System.Drawing.Point(777, 34);
            this.TintCharacter_CheckBox.Name = "TintCharacter_CheckBox";
            this.TintCharacter_CheckBox.Size = new System.Drawing.Size(114, 17);
            this.TintCharacter_CheckBox.TabIndex = 35;
            this.TintCharacter_CheckBox.Text = "Tint Character?";
            this.toolTip1.SetToolTip(this.TintCharacter_CheckBox, "Tint Screen?");
            this.TintCharacter_CheckBox.UseVisualStyleBackColor = true;
            this.TintCharacter_CheckBox.CheckedChanged += new System.EventHandler(this.TintCharacter_CheckBox_CheckedChanged);
            // 
            // Play_Sound_Button
            // 
            this.Play_Sound_Button.Location = new System.Drawing.Point(950, 168);
            this.Play_Sound_Button.Name = "Play_Sound_Button";
            this.Play_Sound_Button.Size = new System.Drawing.Size(75, 21);
            this.Play_Sound_Button.TabIndex = 21;
            this.Play_Sound_Button.Text = "Play Sound";
            this.Play_Sound_Button.UseVisualStyleBackColor = true;
            this.Play_Sound_Button.Click += new System.EventHandler(this.Play_Sound_Button_Click);
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1074, 24);
            this.menuStrip1.TabIndex = 22;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newToolStripMenuItem,
            this.openToolStripMenuItem,
            this.saveToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // newToolStripMenuItem
            // 
            this.newToolStripMenuItem.Name = "newToolStripMenuItem";
            this.newToolStripMenuItem.Size = new System.Drawing.Size(103, 22);
            this.newToolStripMenuItem.Text = "New";
            this.newToolStripMenuItem.Click += new System.EventHandler(this.newToolStripMenuItem_Click);
            // 
            // openToolStripMenuItem
            // 
            this.openToolStripMenuItem.Name = "openToolStripMenuItem";
            this.openToolStripMenuItem.Size = new System.Drawing.Size(103, 22);
            this.openToolStripMenuItem.Text = "Open";
            this.openToolStripMenuItem.Click += new System.EventHandler(this.openToolStripMenuItem_Click);
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(103, 22);
            this.saveToolStripMenuItem.Text = "Save";
            this.saveToolStripMenuItem.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
            // 
            // TintScreenRed_numericUpDown
            // 
            this.TintScreenRed_numericUpDown.Location = new System.Drawing.Point(1005, 57);
            this.TintScreenRed_numericUpDown.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.TintScreenRed_numericUpDown.Name = "TintScreenRed_numericUpDown";
            this.TintScreenRed_numericUpDown.Size = new System.Drawing.Size(40, 20);
            this.TintScreenRed_numericUpDown.TabIndex = 24;
            this.TintScreenRed_numericUpDown.ValueChanged += new System.EventHandler(this.TintScreenRed_numericUpDown_ValueChanged);
            // 
            // TintScreenGreen_numericUpDown
            // 
            this.TintScreenGreen_numericUpDown.Location = new System.Drawing.Point(1005, 83);
            this.TintScreenGreen_numericUpDown.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.TintScreenGreen_numericUpDown.Name = "TintScreenGreen_numericUpDown";
            this.TintScreenGreen_numericUpDown.Size = new System.Drawing.Size(40, 20);
            this.TintScreenGreen_numericUpDown.TabIndex = 25;
            this.TintScreenGreen_numericUpDown.ValueChanged += new System.EventHandler(this.TintScreenGreen_numericUpDown_ValueChanged);
            // 
            // TintScreenBlue_numericUpDown
            // 
            this.TintScreenBlue_numericUpDown.Location = new System.Drawing.Point(1005, 109);
            this.TintScreenBlue_numericUpDown.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.TintScreenBlue_numericUpDown.Name = "TintScreenBlue_numericUpDown";
            this.TintScreenBlue_numericUpDown.Size = new System.Drawing.Size(40, 20);
            this.TintScreenBlue_numericUpDown.TabIndex = 26;
            this.TintScreenBlue_numericUpDown.ValueChanged += new System.EventHandler(this.TintScreenBlue_numericUpDown_ValueChanged);
            // 
            // TintScreenAlpha_numericUpDown
            // 
            this.TintScreenAlpha_numericUpDown.Location = new System.Drawing.Point(1005, 134);
            this.TintScreenAlpha_numericUpDown.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.TintScreenAlpha_numericUpDown.Name = "TintScreenAlpha_numericUpDown";
            this.TintScreenAlpha_numericUpDown.Size = new System.Drawing.Size(40, 20);
            this.TintScreenAlpha_numericUpDown.TabIndex = 27;
            this.TintScreenAlpha_numericUpDown.Value = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.TintScreenAlpha_numericUpDown.ValueChanged += new System.EventHandler(this.TintScreenAlpha_numericUpDown_ValueChanged);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(947, 57);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(33, 15);
            this.label5.TabIndex = 28;
            this.label5.Text = "Red";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(832, 179);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(76, 15);
            this.label6.TabIndex = 31;
            this.label6.Text = "Wait Timer";
            // 
            // OpenFileDialog
            // 
            this.OpenFileDialog.FileName = "\"\"";
            this.OpenFileDialog.Filter = "XML Files (*.xml|*.xml)";
            this.OpenFileDialog.Title = "Select a File to Open";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.Location = new System.Drawing.Point(947, 83);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(46, 15);
            this.label7.TabIndex = 33;
            this.label7.Text = "Green";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label8.Location = new System.Drawing.Point(947, 109);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(36, 15);
            this.label8.TabIndex = 34;
            this.label8.Text = "Blue";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label9.Location = new System.Drawing.Point(947, 134);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(43, 15);
            this.label9.TabIndex = 29;
            this.label9.Text = "Alpha";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label11.Location = new System.Drawing.Point(774, 109);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(36, 15);
            this.label11.TabIndex = 43;
            this.label11.Text = "Blue";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label12.Location = new System.Drawing.Point(774, 83);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(46, 15);
            this.label12.TabIndex = 42;
            this.label12.Text = "Green";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label13.Location = new System.Drawing.Point(774, 57);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(33, 15);
            this.label13.TabIndex = 40;
            this.label13.Text = "Red";
            // 
            // TintCharacterBlue_NumericUpDown
            // 
            this.TintCharacterBlue_NumericUpDown.Location = new System.Drawing.Point(832, 109);
            this.TintCharacterBlue_NumericUpDown.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.TintCharacterBlue_NumericUpDown.Name = "TintCharacterBlue_NumericUpDown";
            this.TintCharacterBlue_NumericUpDown.Size = new System.Drawing.Size(40, 20);
            this.TintCharacterBlue_NumericUpDown.TabIndex = 38;
            this.TintCharacterBlue_NumericUpDown.ValueChanged += new System.EventHandler(this.TintCharacterBlue_NumericUpDown_ValueChanged);
            // 
            // TintCharacterGreen_NumericUpDown
            // 
            this.TintCharacterGreen_NumericUpDown.Location = new System.Drawing.Point(832, 83);
            this.TintCharacterGreen_NumericUpDown.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.TintCharacterGreen_NumericUpDown.Name = "TintCharacterGreen_NumericUpDown";
            this.TintCharacterGreen_NumericUpDown.Size = new System.Drawing.Size(40, 20);
            this.TintCharacterGreen_NumericUpDown.TabIndex = 37;
            this.TintCharacterGreen_NumericUpDown.ValueChanged += new System.EventHandler(this.TintCharacterGreen_NumericUpDown_ValueChanged);
            // 
            // TintCharacterRed_NumericUpDown
            // 
            this.TintCharacterRed_NumericUpDown.Location = new System.Drawing.Point(832, 57);
            this.TintCharacterRed_NumericUpDown.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.TintCharacterRed_NumericUpDown.Name = "TintCharacterRed_NumericUpDown";
            this.TintCharacterRed_NumericUpDown.Size = new System.Drawing.Size(40, 20);
            this.TintCharacterRed_NumericUpDown.TabIndex = 36;
            this.TintCharacterRed_NumericUpDown.ValueChanged += new System.EventHandler(this.TintCharacterRed_NumericUpDown_ValueChanged);
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label10.Location = new System.Drawing.Point(832, 152);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(43, 15);
            this.label10.TabIndex = 45;
            this.label10.Text = "Zoom";
            // 
            // Zoom_NumericUpDown1
            // 
            this.Zoom_NumericUpDown1.Location = new System.Drawing.Point(770, 152);
            this.Zoom_NumericUpDown1.Maximum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.Zoom_NumericUpDown1.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.Zoom_NumericUpDown1.Name = "Zoom_NumericUpDown1";
            this.Zoom_NumericUpDown1.Size = new System.Drawing.Size(56, 20);
            this.Zoom_NumericUpDown1.TabIndex = 44;
            this.Zoom_NumericUpDown1.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.Zoom_NumericUpDown1.ValueChanged += new System.EventHandler(this.Zoom_NumericUpDown1_ValueChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.DarkTurquoise;
            this.ClientSize = new System.Drawing.Size(1074, 780);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.Zoom_NumericUpDown1);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.WaitTime_NumericUpDown);
            this.Controls.Add(this.Animation_Partially_Completed_CheckBox);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.Relative_to_Screen_Checkbox);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.TintCharacter_CheckBox);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.TintCharacterBlue_NumericUpDown);
            this.Controls.Add(this.TintCharacterGreen_NumericUpDown);
            this.Controls.Add(this.TintCharacterRed_NumericUpDown);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.SwapSprite_Button);
            this.Controls.Add(this.Tint_screen_Checkbox);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.Paste_Frame_Button);
            this.Controls.Add(this.TintScreenAlpha_numericUpDown);
            this.Controls.Add(this.Clear_Frame_Button);
            this.Controls.Add(this.TintScreenBlue_numericUpDown);
            this.Controls.Add(this.TintScreenGreen_numericUpDown);
            this.Controls.Add(this.TintScreenRed_numericUpDown);
            this.Controls.Add(this.Copy_Frame_Button);
            this.Controls.Add(this.PlayAnimation_Button);
            this.Controls.Add(this.TextureHeight_NumericUpDown);
            this.Controls.Add(this.MouseCoords_TextBox);
            this.Controls.Add(this.Remove_Frame_Button);
            this.Controls.Add(this.TextureWidth_NumericUpDown);
            this.Controls.Add(this.Add_Frame_Button);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.AnimationPicture_UVCoords_Panel);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.AnimationFrames_Listview);
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.AnimationPanel);
            this.Controls.Add(this.menuStrip1);
            this.Controls.Add(this.Play_Sound_Button);
            this.Controls.Add(this.Sounds_ComboBox);
            this.Controls.Add(this.Remove_Sprite_Button);
            this.Controls.Add(this.Add_Sprite_Button);
            this.MainMenuStrip = this.menuStrip1;
            this.MinimumSize = new System.Drawing.Size(1045, 801);
            this.Name = "Form1";
            this.Text = "AnimationEditor";
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.TextureHeight_NumericUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.TextureWidth_NumericUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.WaitTime_NumericUpDown)).EndInit();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.TintScreenRed_numericUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.TintScreenGreen_numericUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.TintScreenBlue_numericUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.TintScreenAlpha_numericUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.TintCharacterBlue_NumericUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.TintCharacterGreen_NumericUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.TintCharacterRed_NumericUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Zoom_NumericUpDown1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Panel AnimationPanel;
        private System.Windows.Forms.ListView AnimationFrames_Listview;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.ColumnHeader columnHeader1;
        private System.Windows.Forms.Button Fire1_Button;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button Heal3_Button;
        private System.Windows.Forms.Panel AnimationPicture_UVCoords_Panel;
        private System.Windows.Forms.Button Add_Frame_Button;
        private System.Windows.Forms.Button Remove_Frame_Button;
        private System.Windows.Forms.Button Copy_Frame_Button;
        private System.Windows.Forms.Button Clear_Frame_Button;
        private System.Windows.Forms.Button Paste_Frame_Button;
        private System.Windows.Forms.TextBox MouseCoords_TextBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.NumericUpDown TextureHeight_NumericUpDown;
        private System.Windows.Forms.NumericUpDown TextureWidth_NumericUpDown;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ToolTip toolTip1;
        private System.Windows.Forms.Button Remove_Sprite_Button;
        private System.Windows.Forms.Button Add_Sprite_Button;
        private System.Windows.Forms.CheckBox Relative_to_Screen_Checkbox;
        private System.Windows.Forms.CheckBox Animation_Partially_Completed_CheckBox;
        private System.Windows.Forms.ComboBox Sounds_ComboBox;
        private System.Windows.Forms.Button Play_Sound_Button;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.CheckBox Tint_screen_Checkbox;
        private System.Windows.Forms.NumericUpDown TintScreenRed_numericUpDown;
        private System.Windows.Forms.NumericUpDown TintScreenGreen_numericUpDown;
        private System.Windows.Forms.NumericUpDown TintScreenBlue_numericUpDown;
        private System.Windows.Forms.NumericUpDown TintScreenAlpha_numericUpDown;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button PlayAnimation_Button;
        private System.Windows.Forms.NumericUpDown WaitTime_NumericUpDown;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.OpenFileDialog OpenFileDialog;
        private System.Windows.Forms.Button SwapSprite_Button;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.CheckBox TintCharacter_CheckBox;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.NumericUpDown TintCharacterBlue_NumericUpDown;
        private System.Windows.Forms.NumericUpDown TintCharacterGreen_NumericUpDown;
        private System.Windows.Forms.NumericUpDown TintCharacterRed_NumericUpDown;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.NumericUpDown Zoom_NumericUpDown1;
    }
}

