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
        //====================================
        //  Animation Picture Panel ~ Paint
        //====================================
        private void AnimationPicture_UVCoords_Panel_Paint(object sender, PaintEventArgs e)
        {
            System.Drawing.Pen TempPen = new Pen(Color.WhiteSmoke);
            e.Graphics.DrawImage(GetImageFromList(GetImageNameByState()), 0, 0, AnimationPicture_UVCoords_Panel.Width, AnimationPicture_UVCoords_Panel.Height);
            e.Graphics.DrawRectangle(TempPen, m_AnimationPicture_UVCoords_Panel_Rect);
            TempPen.Dispose();
        }

        //====================================
        //  Animation Picture Panel ~ MouseMove
        //====================================
        private void AnimationPicture_UVCoords_Panel_MouseMove(object sender, MouseEventArgs e)
        {
            MouseCoords_TextBox.Text = "X=" + e.X.ToString() + ", Y=" + e.Y.ToString();
        }

        //====================================
        //  Animation Picture Panel ~ MouseClick
        //====================================
        private void AnimationPicture_UVCoords_Panel_MouseClick(object sender, MouseEventArgs e)
        {
            int iTotalSpriteColsInImage = 5;
            int iTotalSpriteRowsInImage = 0;
            for (int i = 0; i < GetImageFromList(GetImageNameByState()).Height; i += 192) 
            { 
                iTotalSpriteRowsInImage += 1; 
            }



            float BlitX = ((float)((int)(((float)e.X / (float)AnimationPicture_UVCoords_Panel.Width)  * 10)) / 10);
            float BlitY = ((float)((int)(((float)e.Y / (float)AnimationPicture_UVCoords_Panel.Height) * 10)) / 10);
            for (int i = iTotalSpriteColsInImage; i != -1; i--)
            {
                float BlitVal = (float)i / (float)iTotalSpriteColsInImage;
                if (BlitX >= BlitVal)
                {
                    BlitX = BlitVal;
                    break;
                }
            }
            for (int i = iTotalSpriteRowsInImage; i != -1; i--)
            {
                float BlitVal = (float)i / (float)iTotalSpriteRowsInImage;
                if (BlitY >= BlitVal)
                {
                    BlitY = BlitVal;
                    break;
                }
            }

            m_AnimationPicture_UVCoords_Panel_Rect.X        = (int)(BlitX * AnimationPicture_UVCoords_Panel.Width);
            m_AnimationPicture_UVCoords_Panel_Rect.Y        = (int)(BlitY * AnimationPicture_UVCoords_Panel.Height);
            m_AnimationPicture_UVCoords_Panel_Rect.Width    = (int)((1.0 / iTotalSpriteColsInImage) * AnimationPicture_UVCoords_Panel.Width);
            m_AnimationPicture_UVCoords_Panel_Rect.Height   = (int)((1.0 / iTotalSpriteRowsInImage) * AnimationPicture_UVCoords_Panel.Height);
            AnimationPicture_UVCoords_Panel.Invalidate();
        }
    }
}
