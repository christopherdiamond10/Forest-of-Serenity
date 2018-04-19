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
        //================================================
        //  AnimationFrames_Listview ~ Changed Selection
        //================================================
        private void AnimationFrames_Listview_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (AnimationFrames_Listview.SelectedIndices.Count > 0) 
            {
                // Set CurrentFrame Selected and Current Sprite Selection
                m_iCurrentFrameIndex          = AnimationFrames_Listview.SelectedIndices[0];
                m_iCurrentlySelectedTextureID = -1;


                // Modify the Main Controls display to current chosen options
                if (m_AnimationFrameInfoList.Count > m_iCurrentFrameIndex)
                {
                    Tint_screen_Checkbox.Checked            = m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_bTintScreen;
                    TintScreenRed_numericUpDown.Value       = m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_iTintScreenRed;
                    TintScreenGreen_numericUpDown.Value     = m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_iTintScreenGreen;
                    TintScreenBlue_numericUpDown.Value      = m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_iTintScreenBlue;
                    TintScreenAlpha_numericUpDown.Value     = m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_iTintScreenAlpha;

                    TintCharacter_CheckBox.Checked          = m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_bTintCharacter;
                    TintCharacterRed_NumericUpDown.Value    = m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_iTintCharacterRed;
                    TintCharacterGreen_NumericUpDown.Value  = m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_iTintCharacterGreen;
                    TintCharacterBlue_NumericUpDown.Value   = m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_iTintCharacterBlue;

                    Sounds_ComboBox.Text = m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_sSoundFilename;
                    Sounds_ComboBox.Text = Sounds_ComboBox.Text != "" ? Sounds_ComboBox.Text : "(No Sound)";

                    WaitTime_NumericUpDown.Value = m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_iWaitTimeTillNextFrame;

                    Animation_Partially_Completed_CheckBox.Checked = m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_bAnimationPartiallyCompleted;
                }

                // Update Panel
                AnimationPanel.Invalidate();
            }
        }



        //================================================
        //  Add Frame Button
        //================================================
        private void Add_Frame_Button_Click(object sender, EventArgs e)
        {
            int Count = AnimationFrames_Listview.Items.Count;
            AnimationFrames_Listview.Items.Add("Frame" + (Count + 1 < 10 ? "0" : "") + (Count + 1).ToString());

            // Create New Info Class, and fill it up with the same information as the previous Frame.
            AnimatedFrameInfo AnimFrameInfo = CopyAnimFrameInfo(m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex));

            // Increment Frame Index
            m_iCurrentFrameIndex++;

            // Deselect Any Textures
            m_iCurrentlySelectedTextureID = -1;

            // Make Selection Visible in the ListView
            AnimationFrames_Listview.Items[m_iCurrentFrameIndex].Selected = true;

            // Add New Info Class to the Correct Insertion Location
            m_AnimationFrameInfoList.Insert(m_iCurrentFrameIndex, AnimFrameInfo);


            // Modify Main Control Options to Show updated selection
            Tint_screen_Checkbox.Checked        = AnimFrameInfo.m_bTintScreen;
            TintScreenRed_numericUpDown.Value   = AnimFrameInfo.m_iTintScreenRed;
            TintScreenGreen_numericUpDown.Value = AnimFrameInfo.m_iTintScreenGreen;
            TintScreenBlue_numericUpDown.Value  = AnimFrameInfo.m_iTintScreenBlue;
            TintScreenAlpha_numericUpDown.Value = AnimFrameInfo.m_iTintScreenAlpha;

            TintCharacter_CheckBox.Checked         = AnimFrameInfo.m_bTintCharacter;
            TintCharacterRed_NumericUpDown.Value   = AnimFrameInfo.m_iTintCharacterRed;
            TintCharacterGreen_NumericUpDown.Value = AnimFrameInfo.m_iTintCharacterGreen;
            TintCharacterBlue_NumericUpDown.Value  = AnimFrameInfo.m_iTintCharacterBlue;

            Sounds_ComboBox.Text = AnimFrameInfo.m_sSoundFilename;
            Sounds_ComboBox.Text = Sounds_ComboBox.Text != "" ? Sounds_ComboBox.Text : "(No Sound)";
        }


        //================================================
        //  Remove Frame Button
        //================================================
        private void Remove_Frame_Button_Click(object sender, EventArgs e)
        {
            AnimationFrames_Listview.Items.RemoveAt(AnimationFrames_Listview.Items.Count - 1);
            m_AnimationFrameInfoList.RemoveAt(m_iCurrentFrameIndex);
            if (m_iCurrentFrameIndex >= AnimationFrames_Listview.Items.Count) { m_iCurrentFrameIndex = AnimationFrames_Listview.Items.Count - 1; }
            m_iCurrentlySelectedTextureID = -1;
            AnimationPanel.Invalidate();
        }


        //================================================
        //  Copy Frame Button
        //================================================
        private void Copy_Frame_Button_Click(object sender, EventArgs e)
        {
            CopyAnimFrameInfo(m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex), m_AnimFrameInfo_ClipboardCopy);
        }


        //================================================
        //  Paste Frame Button
        //================================================
        private void Paste_Frame_Button_Click(object sender, EventArgs e)
        {
            m_AnimationFrameInfoList.RemoveAt(m_iCurrentFrameIndex);
            m_AnimationFrameInfoList.Insert(m_iCurrentFrameIndex, CopyAnimFrameInfo(m_AnimFrameInfo_ClipboardCopy));
            m_iCurrentlySelectedTextureID = -1;
            AnimationPanel.Invalidate();
        }


        //================================================
        //  Clear Frame Button
        //================================================
        private void Clear_Frame_Button_Click(object sender, EventArgs e)
        {
            m_AnimationFrameInfoList.RemoveAt(m_iCurrentFrameIndex);
            m_AnimationFrameInfoList.Insert(m_iCurrentFrameIndex, new AnimatedFrameInfo());
            m_iCurrentlySelectedTextureID = -1;
            AnimationPanel.Invalidate();
        }




        //================================================
        //  Copy Frame Info ~ Function
        //================================================
        private AnimatedFrameInfo CopyAnimFrameInfo(AnimatedFrameInfo CopySource, AnimatedFrameInfo TargetSource = null)
        {
            if (TargetSource == null) { TargetSource = new AnimatedFrameInfo(); }
            foreach (SpriteInfo SprInfo in CopySource.m_SpriteInfoList)
            {
                SpriteInfo Sprite   = new SpriteInfo();
                Sprite.ID           = SprInfo.ID;
                Sprite.X            = SprInfo.X;
                Sprite.Y            = SprInfo.Y;
                Sprite.W            = SprInfo.W;
                Sprite.H            = SprInfo.H;
                Sprite.Texture      = SprInfo.Texture;
                Sprite.TextureName  = SprInfo.TextureName;
                Sprite.BlitRect     = SprInfo.BlitRect;
                TargetSource.m_SpriteInfoList.Add(Sprite);
            }
            TargetSource.m_bTintScreen                  = CopySource.m_bTintScreen;
            TargetSource.m_iTintScreenRed               = CopySource.m_iTintScreenRed;
            TargetSource.m_iTintScreenGreen             = CopySource.m_iTintScreenGreen;
            TargetSource.m_iTintScreenBlue              = CopySource.m_iTintScreenBlue;
            TargetSource.m_iTintScreenAlpha             = CopySource.m_iTintScreenAlpha;
            TargetSource.m_bTintCharacter               = CopySource.m_bTintCharacter;
            TargetSource.m_iTintCharacterRed            = CopySource.m_iTintCharacterRed;
            TargetSource.m_iTintCharacterGreen          = CopySource.m_iTintCharacterGreen;
            TargetSource.m_iTintCharacterBlue           = CopySource.m_iTintCharacterBlue;
            TargetSource.m_bAnimationPartiallyCompleted = CopySource.m_bAnimationPartiallyCompleted;
            return TargetSource;
        }
    }
}
