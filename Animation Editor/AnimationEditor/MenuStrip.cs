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
        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ResetEverything();
            AnimationPanel.Invalidate();
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog.FileName = "";
            OpenFileDialog.Filter = "XML Files (*.xml)|*.xml";

            if (OpenFileDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                if (ResetEverything())
                {
                    // Read XML
                    m_oClassXML.ReadFromXML(OpenFileDialog.FileName);

                    // Convert XML Animation To Editor Version
                    m_AnimationFrameInfoList = ConvertListValuesBetweenGameandEditor(m_oClassXML.GetAnimFrameInfoList(), false);

                    // Add In the Animation Frames to the List
                    for (; AnimationFrames_Listview.Items.Count < m_AnimationFrameInfoList.Count;) 
                    {
                        AnimationFrames_Listview.Items.Add("Frame" + (AnimationFrames_Listview.Items.Count + 1 < 10 ? "0" : "") + (AnimationFrames_Listview.Items.Count + 1).ToString()); 
                    }

                    // Set Current Frame to Select and deselect Sprites
                    m_iCurrentFrameIndex = 0;
                    m_iCurrentlySelectedTextureID = -1;

                    // Check Boxes As Appropriate
                    Relative_to_Screen_Checkbox.Checked = m_oClassXML.GetRelativeToScreen();

                    // Update Panel
                    AnimationPanel.Invalidate();
                }
            }
        }

        
        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            m_oClassXML.WriteToXML(ConvertListValuesBetweenGameandEditor(m_AnimationFrameInfoList), Relative_to_Screen_Checkbox.Checked);
        }



        private List<AnimatedFrameInfo> ConvertListValuesBetweenGameandEditor(List<AnimatedFrameInfo> AFIL, bool ConvertingtoGame = true, bool RelativeToScreen = false)
        {
            List<AnimatedFrameInfo> ReturnAFIL = new List<AnimatedFrameInfo>();
            foreach (AnimatedFrameInfo CopyAFI in AFIL)
            {
                AnimatedFrameInfo AFI = new AnimatedFrameInfo();
                AFI.m_bAnimationPartiallyCompleted  = CopyAFI.m_bAnimationPartiallyCompleted;
                AFI.m_bTintScreen                   = CopyAFI.m_bTintScreen;
                AFI.m_iTintScreenAlpha              = CopyAFI.m_iTintScreenAlpha;
                AFI.m_iTintScreenBlue               = CopyAFI.m_iTintScreenBlue;
                AFI.m_iTintScreenGreen              = CopyAFI.m_iTintScreenGreen;
                AFI.m_iTintScreenRed                = CopyAFI.m_iTintScreenRed;
                AFI.m_bTintCharacter                = CopyAFI.m_bTintCharacter;
                AFI.m_iTintCharacterBlue            = CopyAFI.m_iTintCharacterBlue;
                AFI.m_iTintCharacterGreen           = CopyAFI.m_iTintCharacterGreen;
                AFI.m_iTintCharacterRed             = CopyAFI.m_iTintCharacterRed;
                AFI.m_iWaitTimeTillNextFrame        = CopyAFI.m_iWaitTimeTillNextFrame;
                AFI.m_sSoundFilename                = CopyAFI.m_sSoundFilename;
                foreach (SpriteInfo CopySprInfo in CopyAFI.m_SpriteInfoList)
                {
                    SpriteInfo SprInfo  = new SpriteInfo();
                    if (!RelativeToScreen)
                    {
                        SprInfo.X = ConvertingtoGame ? CopySprInfo.X - m_EnemySprInfo.X : CopySprInfo.X + m_EnemySprInfo.X;
                        SprInfo.Y = ConvertingtoGame ? CopySprInfo.Y - m_EnemySprInfo.Y : CopySprInfo.Y + m_EnemySprInfo.Y;
                    }
                    else
                    {
                        SprInfo.X = CopySprInfo.X - m_EnemySprInfo.X;
                        SprInfo.Y = CopySprInfo.Y - m_EnemySprInfo.Y;
                    }
                    SprInfo.W           = CopySprInfo.W;
                    SprInfo.H           = CopySprInfo.H;
                    SprInfo.TextureName = CopySprInfo.TextureName;
                    SprInfo.Texture     = CopySprInfo.Texture;
                    SprInfo.ID          = CopySprInfo.ID;
                    SprInfo.BlitRect    = CopySprInfo.BlitRect;

                    // If Converting Back into Editor, changes need to be made to the Blitrect and an Image needs to passed in.
                    if (!ConvertingtoGame)
                    {
                        float BlitX = (float)((float)SprInfo.BlitRect.X * 0.001);
                        float BlitY = (float)((float)SprInfo.BlitRect.Y * 0.001);
                        float BlitW = (float)((float)SprInfo.BlitRect.Width * 0.001) - BlitX;
                        float BlitH = (float)((float)SprInfo.BlitRect.Height * 0.001) - BlitY;

                        // Attempt to Get Texture IF there is None
                        if (SprInfo.Texture == null) { SprInfo.Texture = GetImageFromList("./Images/" + SprInfo.TextureName); }
                        if( SprInfo.Texture != null)
                        {
                            SprInfo.BlitRect.X      = (int)(BlitX * SprInfo.Texture.Width);
                            SprInfo.BlitRect.Y      = (int)(BlitY * SprInfo.Texture.Height);
                            SprInfo.BlitRect.Width  = (int)(BlitW * SprInfo.Texture.Width);
                            SprInfo.BlitRect.Height = (int)(BlitH * SprInfo.Texture.Height);
                        }
                    }
                    AFI.m_SpriteInfoList.Add(SprInfo);
                }
                ReturnAFIL.Add(AFI);
            }


            // Another Conversion Between the Game and this Editor.
            // The game skips the first frame due to the way the Update and Draw functions are set up,
            // so we add in a new frame to the first element before saving.
            // When returning we simply remove that element.
            if (ConvertingtoGame)
            {
                ReturnAFIL.Insert(0, new AnimatedFrameInfo());
            }
            else
            {
                ReturnAFIL.RemoveAt(0);
            }
            return ReturnAFIL;
        }
    }
}
