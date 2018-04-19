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
        private Rectangle GetRect(SpriteInfo Sprite)
        {
            int W = Sprite.W * m_iZoom;
            int H = Sprite.H * m_iZoom;
            int X = Sprite.X - (int)(((float)Sprite.W / AnimationPanel.Width) * W);
            int Y = Sprite.Y - (int)(((float)Sprite.H / AnimationPanel.Height) * H);

            return new Rectangle(X, Y, W, H);
        }
        //====================================
        // Animation Panel Paint
        //====================================
        private void AnimationPanel_Paint(object sender, PaintEventArgs e)
        {
            // Draw Enemy
            DrawAnimationPanelEnemy();


            // Draw Animation Sprites
            foreach (SpriteInfo Sprite in m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_SpriteInfoList)
            {
                Rectangle Rect = GetRect(Sprite);
                e.Graphics.DrawImage(Sprite.Texture, Rect, Sprite.BlitRect, GraphicsUnit.Pixel);
            }


            // Draw Tint Screen
            if (m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_bTintScreen)
            {
                m_oPen_and_Brush.BrushColour = GetTintScreenColour();
                Rectangle Rect = new Rectangle(0, 0, AnimationPanel.Width, AnimationPanel.Height);
                e.Graphics.FillRectangle(m_oPen_and_Brush.ClassBrush, Rect);
            }
        }

        //=============================================
        // Animation Panel MouseMove
        //=============================================
        private void AnimationPanel_MouseMove(object sender, MouseEventArgs e)
        {
            MouseCoords_TextBox.Text = "X=" + e.X.ToString() + ", Y=" + e.Y.ToString();

            // Set Move Mode to False if out of bounds
            if (e.X == 0 || e.X >= AnimationPanel.Width - 5 || e.Y == 0 || e.Y >= AnimationPanel.Height - 5) { m_bMoveSpriteMode = false; }

            // If Not Removing Sprites
            if (m_iSpriteAddRemoveStatePlaceHolder == (uint)SpriteAddRemoveState.AddSpriteMode)
            {
                // Move Sprite if we have chosen to do so
                if (m_bMoveSpriteMode && m_iCurrentlySelectedTextureID >= 0)
                {
                    MouseMoveSprite(e.X, e.Y);
                }

                // Otherwise Highlight any Sprite we're hovering over
                else
                {
                    HighlightSpritesOnAnimationPanel(e.X, e.Y);
                }
            }

            // Otherwise If Removing Sprites
            else
            {
                // Just Highlight the Sprite That Will Be Deleted
                HighlightSpritesOnAnimationPanel(e.X, e.Y);
            }
        }

        //====================================
        // Animation Panel MouseClick
        //====================================
        private void AnimationPanel_MouseClick(object sender, MouseEventArgs e)
        {
            // Get Currently Selected Tetxure
            int iSelectedTexture = Get_IsMousePositionHoveringOverTexture(e.X, e.Y);

            // If Adding Sprites to Panel
            if (m_iSpriteAddRemoveStatePlaceHolder == (uint)SpriteAddRemoveState.AddSpriteMode)
            {
                // If No Sprite Is Selected, then Add a New Sprite to the Panel
                if (iSelectedTexture == -1)
                {
                    AddNewSpriteToAnimationPanel(e.X, e.Y);
                }

                // Otherwise if in range of a sprite, select it
                else
                {
                    SelectASpriteOnAnimationPanel(iSelectedTexture);
                }
            }

            // Otherwise Removing Sprites
            else
            {
                RemoveSpriteFromAnimationPanel(iSelectedTexture);
            }
        }



        //====================================
        // Animation Panel MouseDown
        //====================================
        private void AnimationPanel_MouseDown(object sender, MouseEventArgs e)
        {
            if (m_iCurrentlySelectedTextureID >= 0)
            {
                Rectangle Rect = GetRect(m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_SpriteInfoList.ElementAt(m_iCurrentlySelectedTextureID));
                if (((e.X > Rect.X) && (e.X < (Rect.X + Rect.Width))) && ((e.Y > Rect.Y) && (e.Y < (Rect.Y + Rect.Height)))) { m_bMoveSpriteMode = true; }
            }
        }



        //====================================
        // Animation Panel MouseUp
        //====================================
        private void AnimationPanel_MouseUp(object sender, MouseEventArgs e)
        {
            m_bMoveSpriteMode = false;
        }







        //====================================
        // Is Mouse Hovering Over Texture?
        //====================================
        private int Get_IsMousePositionHoveringOverTexture(int a_X, int a_Y)
        {
            foreach (SpriteInfo Sprite in m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_SpriteInfoList)
            {
                Rectangle Rect = GetRect(Sprite);
                if( ((a_X > Rect.X) && (a_X < (Rect.X + Rect.Width)))   &&   ((a_Y > Rect.Y) && (a_Y < (Rect.Y + Rect.Height))) )
                {
                    return (int)Sprite.ID;
                }
            }
            return -1;
        }




        //====================================
        //  Move Sprite
        //====================================
        private void MouseMoveSprite(int Mouse_X, int Mouse_Y)
        {
            int XPos = Mouse_X - (int)((m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_SpriteInfoList.ElementAt(m_iCurrentlySelectedTextureID).W * m_iZoom) * 0.5);
            int YPos = Mouse_Y - (int)((m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_SpriteInfoList.ElementAt(m_iCurrentlySelectedTextureID).H * m_iZoom) * 0.5);
            m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_SpriteInfoList.ElementAt(m_iCurrentlySelectedTextureID).X = XPos;
            m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_SpriteInfoList.ElementAt(m_iCurrentlySelectedTextureID).Y = YPos;
            AnimationPanel.Invalidate();
        }



        //====================================
        // Highlight Sprites
        //====================================
        private void HighlightSpritesOnAnimationPanel(int Mouse_X, int Mouse_Y)
        {
            bool bAlreadyHighighted = false;
            foreach (SpriteInfo Sprite in m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_SpriteInfoList)
            {
                // Unless Already Selected
                if (Sprite.ID != m_iCurrentlySelectedTextureID)
                {
                    Rectangle Rect = GetRect(Sprite);

                    // Highlight if Hovering Over
                    if (((Mouse_X > Rect.X) && (Mouse_X < (Rect.X + Rect.Width))) && ((Mouse_Y > Rect.Y) && (Mouse_Y < (Rect.Y + Rect.Height))) && !bAlreadyHighighted)
                    {
                        m_oPen_and_Brush.PenColour = m_oPen_and_Brush.HighlightedRectColour;
                        m_oPen_and_Brush.ClassGraphics.DrawRectangle(m_oPen_and_Brush.ClassPen, Rect);
                        bAlreadyHighighted = true;
                    }
                    // Unhighlight if Otherwise
                    else
                    {
                        m_oPen_and_Brush.PenColour = AnimationPanel.BackColor;
                        m_oPen_and_Brush.ClassGraphics.DrawRectangle(m_oPen_and_Brush.ClassPen, Rect);
                    }
                }
            }
        }



        //====================================
        // Select Sprite
        //====================================
        private void SelectASpriteOnAnimationPanel(int iSelectedTexture)
        {
            m_iCurrentlySelectedTextureID = iSelectedTexture;

            // Draw Selected Rect
            SpriteInfo Sprite = m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_SpriteInfoList.ElementAt(iSelectedTexture);
            Rectangle Rect = GetRect(Sprite);
            m_oPen_and_Brush.PenColour = m_oPen_and_Brush.SelectedRectColour;
            m_oPen_and_Brush.ClassGraphics.DrawRectangle(m_oPen_and_Brush.ClassPen, Rect);

            // Change NumericUpDown Values
            TextureWidth_NumericUpDown.Value = m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_SpriteInfoList.ElementAt(m_iCurrentlySelectedTextureID).W;
            TextureHeight_NumericUpDown.Value = m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_SpriteInfoList.ElementAt(m_iCurrentlySelectedTextureID).H;
        }



        //====================================
        // Add New Sprite
        //====================================
        private void AddNewSpriteToAnimationPanel(int Mouse_X, int Mouse_Y)
        {
            // Adding a New Sprite to Current Animated Frame
            SpriteInfo SprInfo = new SpriteInfo();
            SprInfo.TextureName = GetImageNameByState();
            SprInfo.Texture = GetImageFromList(SprInfo.TextureName);
            SprInfo.ID = (uint)m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_SpriteInfoList.Count();
            SprInfo.BlitRect = GetAnimationSpriteFullBlitRect(SprInfo.Texture);
            SprInfo.W = 50;
            SprInfo.H = 50;
            SprInfo.X = (Mouse_X - (int)(SprInfo.W * 0.5));
            SprInfo.Y = (Mouse_Y - (int)(SprInfo.H * 0.5));
            m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_SpriteInfoList.Add(SprInfo);
            ///////////////////////////////////////////////////////////////////////////////////

            // Select the Sprite
            if (m_iCurrentlySelectedTextureID >= 0)
            {
                SpriteInfo Sprite = m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_SpriteInfoList.ElementAt(m_iCurrentlySelectedTextureID);
                Rectangle TempRect = GetRect(Sprite);
                m_oPen_and_Brush.PenColour = m_oPen_and_Brush.HighlightedRectColour;
                m_oPen_and_Brush.ClassGraphics.DrawRectangle(m_oPen_and_Brush.ClassPen, TempRect);
            }
            m_iCurrentlySelectedTextureID = (int)SprInfo.ID;

            // Change NumericUpDown Values
            TextureWidth_NumericUpDown.Value = 50;
            TextureHeight_NumericUpDown.Value = 50;

            // Draw the Sprite
            Rectangle Rect = GetRect(SprInfo);
            m_oPen_and_Brush.ClassGraphics.DrawImage(SprInfo.Texture, Rect, SprInfo.BlitRect, GraphicsUnit.Pixel);

            // Draw Selected Rect
            m_oPen_and_Brush.PenColour = m_oPen_and_Brush.SelectedRectColour;
            m_oPen_and_Brush.ClassGraphics.DrawRectangle(m_oPen_and_Brush.ClassPen, Rect);
        }




        //====================================
        // Add New Sprite
        //====================================
        private void RemoveSpriteFromAnimationPanel(int iSelectedTexture)
        {
            if (iSelectedTexture >= 0)
            {
                m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_SpriteInfoList.RemoveAt(iSelectedTexture);
                foreach (SpriteInfo SprInfo in m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_SpriteInfoList)
                {
                    if (SprInfo.ID > iSelectedTexture)
                    {
                        SprInfo.ID--;
                    }
                }
                m_iCurrentlySelectedTextureID = -1;
                AnimationPanel.Invalidate();
            }
        }



        //====================================
        // Draw Enemy
        //====================================
        private void DrawAnimationPanelEnemy()
        {
            Rectangle Rect = GetRect(m_EnemySprInfo);

            if( m_iCurrentFrameIndex >= 0 && m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_bTintCharacter)
            {
                Bitmap bitmap = new Bitmap(m_EnemySprInfo.Texture);
                int R = m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_iTintCharacterRed;
                int G = m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_iTintCharacterGreen;
                int B = m_AnimationFrameInfoList.ElementAt(m_iCurrentFrameIndex).m_iTintCharacterBlue;
                Color Tint = Color.FromArgb(R, G, B);

                for (int TempX = 0; TempX < bitmap.Width; TempX++)
                {
                    for (int TempY = 0; TempY < bitmap.Height; TempY++)
                    {
                        if (bitmap.GetPixel(TempX, TempY).A == 0) { continue; }                        
                        bitmap.SetPixel(TempX, TempY, Tint);
                    }
                }
                m_oPen_and_Brush.ClassGraphics.DrawImage(bitmap, Rect);
            }
            else
            {
                m_oPen_and_Brush.ClassGraphics.DrawImage(m_EnemySprInfo.Texture, Rect);
            }
        }
    }
}
