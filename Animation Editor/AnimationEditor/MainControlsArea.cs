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
        //  Play Animation Button
        //================================================
        private void PlayAnimation_Button_Click(object sender, EventArgs e)
        {
            PlayCompleteAnimation();
        }

        //================================================
        //  Tint Screen? ~ Checkbox
        //================================================
        private void Tint_screen_Checkbox_CheckedChanged(object sender, EventArgs e)
        {
            m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_bTintScreen = Tint_screen_Checkbox.Checked;
            AnimationPanel.Invalidate();
        }

        //================================================
        //  Tint Screen Red ~ NumericUpDown
        //================================================
        private void TintScreenRed_numericUpDown_ValueChanged(object sender, EventArgs e)
        {
            m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_iTintScreenRed = (int)TintScreenRed_numericUpDown.Value;
            if (Tint_screen_Checkbox.Checked) { AnimationPanel.Invalidate(); }
        }

        //================================================
        //  Tint Screen Green ~ NumericUpDown
        //================================================
        private void TintScreenGreen_numericUpDown_ValueChanged(object sender, EventArgs e)
        {
            m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_iTintScreenGreen = (int)TintScreenGreen_numericUpDown.Value;
            if (Tint_screen_Checkbox.Checked) { AnimationPanel.Invalidate(); }
        }

        //================================================
        //  Tint Screen Blue ~ NumericUpDown
        //================================================
        private void TintScreenBlue_numericUpDown_ValueChanged(object sender, EventArgs e)
        {
            m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_iTintScreenBlue = (int)TintScreenBlue_numericUpDown.Value;
            if (Tint_screen_Checkbox.Checked) { AnimationPanel.Invalidate(); }
        }

        //================================================
        //  Tint Screen Alpha ~ NumericUpDown
        //================================================
        private void TintScreenAlpha_numericUpDown_ValueChanged(object sender, EventArgs e)
        {
            m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_iTintScreenAlpha = (int)TintScreenAlpha_numericUpDown.Value;
            if (Tint_screen_Checkbox.Checked) { AnimationPanel.Invalidate(); }
        }


        //================================================
        //  Tint Character ~ Checkbox
        //================================================
        private void TintCharacter_CheckBox_CheckedChanged(object sender, EventArgs e)
        {
            m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_bTintCharacter = TintCharacter_CheckBox.Checked;
            AnimationPanel.Invalidate();
        }

        //================================================
        //  Tint Character Red ~ NumericUpDown
        //================================================
        private void TintCharacterRed_NumericUpDown_ValueChanged(object sender, EventArgs e)
        {
            m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_iTintCharacterRed = (int)TintCharacterRed_NumericUpDown.Value;
            if (TintCharacter_CheckBox.Checked) { DrawAnimationPanelEnemy(); }
        }

        //================================================
        //  Tint Character Green ~ NumericUpDown
        //================================================
        private void TintCharacterGreen_NumericUpDown_ValueChanged(object sender, EventArgs e)
        {
            m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_iTintCharacterGreen = (int)TintCharacterGreen_NumericUpDown.Value;
            if (TintCharacter_CheckBox.Checked) { DrawAnimationPanelEnemy(); }
        }

        //================================================
        //  Tint Character Blue ~ NumericUpDown
        //================================================
        private void TintCharacterBlue_NumericUpDown_ValueChanged(object sender, EventArgs e)
        {
            m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_iTintCharacterBlue = (int)TintCharacterBlue_NumericUpDown.Value;
            if (TintCharacter_CheckBox.Checked) { DrawAnimationPanelEnemy(); }
        }




        //================================================
        //  Zoom ~ NumericUpDown
        //================================================
        private void Zoom_NumericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            m_iZoom = (int)Zoom_NumericUpDown1.Value;
            AnimationPanel.Invalidate();
        }


        //================================================
        //  Wait Time till Next Frame ~ NumericUpDown
        //================================================
        private void WaitTime_NumericUpDown_ValueChanged(object sender, EventArgs e)
        {
            m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_iWaitTimeTillNextFrame = (int)WaitTime_NumericUpDown.Value;
        }




        //================================================
        //  Texture Width ~ NumericUpDown
        //================================================
        private void TextureWidth_NumericUpDown_ValueChanged(object sender, EventArgs e)
        {
            if (m_iCurrentlySelectedTextureID >= 0)
            {
                m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_SpriteInfoList.ElementAt(m_iCurrentlySelectedTextureID).W = (int)TextureWidth_NumericUpDown.Value;
                AnimationPanel.Invalidate();
            }
        }

        //================================================
        //  Texture Height ~ NumericUpDown
        //================================================
        private void TextureHeight_NumericUpDown_ValueChanged(object sender, EventArgs e)
        {
            if (m_iCurrentlySelectedTextureID >= 0)
            {
                m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_SpriteInfoList.ElementAt(m_iCurrentlySelectedTextureID).H = (int)TextureHeight_NumericUpDown.Value;
                AnimationPanel.Invalidate();
            }
        }


        //================================================
        //  Add Sprite Button
        //================================================
        private void Add_Sprite_Button_Click(object sender, EventArgs e)
        {
            if (m_iSpriteAddRemoveStatePlaceHolder == (uint)SpriteAddRemoveState.RemoveSpriteMode)
            {
                m_iSpriteAddRemoveStatePlaceHolder = (uint)SpriteAddRemoveState.AddSpriteMode;
                m_iCurrentlySelectedTextureID = -1;
                AnimationPanel.Invalidate();
            }
        }

        //================================================
        //  Swap Sprite Button
        //================================================
        private void SwapSprite_Button_Click(object sender, EventArgs e)
        {
            if (m_iCurrentlySelectedTextureID >= 0)
            {
                string TextureName = GetImageNameByState();
                Image Texture = GetImageFromList(TextureName);
                m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_SpriteInfoList.ElementAt(m_iCurrentlySelectedTextureID).TextureName  = TextureName;
                m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_SpriteInfoList.ElementAt(m_iCurrentlySelectedTextureID).Texture      = Texture;
                m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_SpriteInfoList.ElementAt(m_iCurrentlySelectedTextureID).BlitRect     = GetAnimationSpriteFullBlitRect(Texture);
                AnimationPanel.Invalidate();
            }
        }

        //================================================
        //  Remove Sprite Button
        //================================================
        private void Remove_Sprite_Button_Click(object sender, EventArgs e)
        {
            if (m_iSpriteAddRemoveStatePlaceHolder == (uint)SpriteAddRemoveState.AddSpriteMode)
            {
                m_iSpriteAddRemoveStatePlaceHolder = (uint)SpriteAddRemoveState.RemoveSpriteMode;
                m_iCurrentlySelectedTextureID = -1;
                AnimationPanel.Invalidate();
            }
        }

        //================================================
        //  Sounds ComboBox
        //================================================
        private void Sounds_ComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (AnimationFrames_Listview.SelectedIndices.Count > 0)
            {
                m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_sSoundFilename = Sounds_ComboBox.Text;
            }
        }

        //================================================
        //  Play Sound Button
        //================================================
        private void Play_Sound_Button_Click(object sender, EventArgs e)
        {
            PlaySelectedSound();
        }

        //================================================
        //  Animation Partially Completed ~ Checkbox
        //================================================
        private void Animation_Partially_Completed_CheckBox_CheckedChanged(object sender, EventArgs e)
        {
            foreach (AnimatedFrameInfo AFI in m_AnimationFrameInfoList) 
            { 
                AFI.m_bAnimationPartiallyCompleted = false; 
            }

            if (Animation_Partially_Completed_CheckBox.Checked)
            {
                m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_bAnimationPartiallyCompleted = true;
            }
        }
    }
}