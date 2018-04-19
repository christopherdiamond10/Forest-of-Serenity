using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace AnimationEditor
{
    public partial class Form1 : Form
    {
        System.Media.SoundPlayer    m_AnimationSoundPlayer                    = new System.Media.SoundPlayer();
        List<AnimationTextureInfo>  m_AnimationTextureInfoList                = new List<AnimationTextureInfo>();
        List<AnimatedFrameInfo>     m_AnimationFrameInfoList                  = new List<AnimatedFrameInfo>();
        AnimatedFrameInfo           m_AnimFrameInfo_ClipboardCopy             = new AnimatedFrameInfo();


        bool                        m_bMoveSpriteMode                         = false;

        uint                        m_iAnimationButtonStatePlaceholder        = (uint)AnimationButtonState.Fire1AnimationButton;
        uint                        m_iSpriteAddRemoveStatePlaceHolder        = (uint)SpriteAddRemoveState.AddSpriteMode;
        int                         m_iCurrentFrameIndex                      = 0;
        int                         m_iCurrentlySelectedTextureID             = -1;
        int                         m_iZoom                                   = 1;

        SpriteInfo                  m_EnemySprInfo                            = new SpriteInfo();
        Rectangle                   m_AnimationPicture_UVCoords_Panel_Rect    = new Rectangle();
        Pen_and_Brush               m_oPen_and_Brush                          = new Pen_and_Brush();
        ClassXML                    m_oClassXML                               = new ClassXML();
        
        //DateTime
        
        //====================================
        //  Constructor
        //====================================
        public Form1()
        {
            InitializeComponent();


            
            // Setup Sound Combo Box
            Sounds_ComboBox.Items.Add("(No Sound)"); // First Element is NO SOUND.
            string[] TempStrArray = System.IO.Directory.GetFiles("./Sound/");
            foreach (string path in TempStrArray) 
            { 
                string FileExtension = System.IO.Path.GetExtension(path);
                if (FileExtension == ".wav" || FileExtension == ".WAV")
                {
                    Sounds_ComboBox.Items.Add(System.IO.Path.GetFileNameWithoutExtension(path));
                }
            }
            Sounds_ComboBox.Text = "(No Sound)";

            ////////// Setup Enemy Texture Info //////////
            m_EnemySprInfo.Texture = Image.FromFile("./Images/Succubus.png");
            m_EnemySprInfo.W = m_EnemySprInfo.Texture.Width;
            m_EnemySprInfo.H = m_EnemySprInfo.Texture.Height;
            m_EnemySprInfo.X = (int)((AnimationPanel.Width   * 0.5) - (m_EnemySprInfo.W * 0.5));
            m_EnemySprInfo.Y = (int)((AnimationPanel.Height  * 0.5) - (m_EnemySprInfo.H * 0.5));
            //////////////////////////////////////////////


            AnimationFrames_Listview.Items.Add("Frame01");
            m_AnimationFrameInfoList.Add(new AnimatedFrameInfo());
            m_AnimationPicture_UVCoords_Panel_Rect    = new Rectangle(0, 0, (int)(AnimationPicture_UVCoords_Panel.Width * 0.2), (int)(AnimationPicture_UVCoords_Panel.Height * 0.5));
            m_oPen_and_Brush.ClassGraphics            = AnimationPanel.CreateGraphics();
        }



        //====================================
        //  Get Image From Current State
        //====================================
        private string GetImageNameByState()
        {
            if (m_iAnimationButtonStatePlaceholder == (uint)AnimationButtonState.Fire1AnimationButton) { return "./Images/Fire1.png"; }
            if (m_iAnimationButtonStatePlaceholder == (uint)AnimationButtonState.Heal3AnimationButton) { return "./Images/Heal3.png"; }
            return null;
        }



        //====================================
        //  Get Image from ImageList
        //====================================
        private Image GetImageFromList(string ImageName)
        {
            // Return Texture If It Already Exists
            foreach (AnimationTextureInfo TextureInfo in m_AnimationTextureInfoList)
            {
                if (ImageName == TextureInfo.TextureName)
                {
                    return TextureInfo.Texture;
                }
            }

            // Otherwise Make it Exist
            if (System.IO.File.Exists(ImageName))
            {
                AnimationTextureInfo TextInfo   = new AnimationTextureInfo();
                TextInfo.TextureName            = ImageName;
                TextInfo.Texture                = Image.FromFile(ImageName);
                m_AnimationTextureInfoList.Add(TextInfo);
                return TextInfo.Texture;
            }
            return null;
        }



        //====================================
        //  Get Tint Screen Colour
        //====================================
        Color GetTintScreenColour()
        {
            return Color.FromArgb(m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_iTintScreenAlpha,
                                  m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_iTintScreenRed,
                                  m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_iTintScreenGreen,
                                  m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_iTintScreenBlue);
        }



        //====================================
        //  Get Full Blit Rect
        //====================================
        private Rectangle GetAnimationSpriteFullBlitRect(Image Sprite)
        {
            int iTotalSpriteColsInImage = 5;
            int iTotalSpriteRowsInImage = 0;
            for (int i = 0; i < Sprite.Height; i += 192)
            {
                iTotalSpriteRowsInImage += 1;
            }
            return new Rectangle(
                (int)(((float)m_AnimationPicture_UVCoords_Panel_Rect.X / AnimationPicture_UVCoords_Panel.Width) * Sprite.Width),
                (int)(((float)m_AnimationPicture_UVCoords_Panel_Rect.Y / AnimationPicture_UVCoords_Panel.Height) * Sprite.Height),
                (int)((1.0 / iTotalSpriteColsInImage) * Sprite.Width),
                (int)((1.0 / iTotalSpriteRowsInImage) * Sprite.Height));

        }



        //====================================
        //  Play Selected Sound
        //====================================
        private void PlaySelectedSound(bool bPlayingSequence = false)
        {
			if (bPlayingSequence)
			{
				string SoundFilename = "./Sound/" + m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_sSoundFilename + ".wav";
				if (System.IO.File.Exists(SoundFilename))
				{
					m_AnimationSoundPlayer.SoundLocation = SoundFilename;
					m_AnimationSoundPlayer.Play();
				}
			}
			else
			{
				string SoundFilename = "./Sound/" + Sounds_ComboBox.SelectedItem + ".wav";
				if (System.IO.File.Exists(SoundFilename))
				{
					m_AnimationSoundPlayer.SoundLocation = SoundFilename;
					m_AnimationSoundPlayer.Play();
				}
			}
        }



        //====================================
        //  Play Complete Animation
        //====================================
        private void PlayCompleteAnimation()
        {
            int iTempCurrentFrameIndexHolder = m_iCurrentFrameIndex;

            // Start at First Element
            m_iCurrentFrameIndex = 0;

            // Play Entire Animation
            while (m_iCurrentFrameIndex < m_AnimationFrameInfoList.Count)
            {
                AnimationPanel.Invalidate();
                AnimationPanel.Update();
                PlaySelectedSound(true);
                System.Threading.Thread.Sleep(m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_iWaitTimeTillNextFrame);
                m_iCurrentFrameIndex++;
            }

            // Go Back to Previously Selected Frame
            m_iCurrentFrameIndex = iTempCurrentFrameIndexHolder;
            AnimationPanel.Invalidate();
        }



        //====================================
        //  Reset Everything
        //====================================
        private bool ResetEverything()
        {
            string sWarning = "WARNING, by performing this action you will lose any unsaved progress, would you like to continue?";
            if (MessageBox.Show(sWarning, "Warning!", MessageBoxButtons.YesNo) == DialogResult.Yes)
            {
                /////////////////////////////////
                m_AnimationFrameInfoList.Clear();
                AnimationFrames_Listview.Clear();
                /////////////////////////////////
                m_AnimationFrameInfoList.Add(new AnimatedFrameInfo());
                AnimationFrames_Listview.Items.Add("Frame01");
                /////////////////////////////////
                m_AnimFrameInfo_ClipboardCopy   = new AnimatedFrameInfo();
                m_bMoveSpriteMode               = false;
                m_iCurrentFrameIndex            = 0;
                m_iCurrentlySelectedTextureID   = -1;
                /////////////////////////////////
                return true;
            }
            return false;
        }















        private void Fire1_Button_Click(object sender, EventArgs e)
        {
            m_iAnimationButtonStatePlaceholder = (uint)AnimationButtonState.Fire1AnimationButton;
            AnimationPicture_UVCoords_Panel.Invalidate();
        }

        private void Heal3_Button_Click(object sender, EventArgs e)
        {
            m_iAnimationButtonStatePlaceholder = (uint)AnimationButtonState.Heal3AnimationButton;
            AnimationPicture_UVCoords_Panel.Invalidate();
        }

    }
}
