using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;


//========================
//  Structs
//========================
struct AnimationTextureInfo
{
    public string   TextureName;
    public Image    Texture; 
};



//========================
//  Enums
//========================
enum SpriteAddRemoveState
{
    AddSpriteMode,
    RemoveSpriteMode,
};


enum AnimationButtonState
{
    Fire1AnimationButton,
    WaterAnimationButton,
    Heal3AnimationButton,
};



//========================
//  Classes
//========================
class SpriteInfo
{
    public uint        ID;
    public Image       Texture;
    public string      TextureName;
    public Rectangle   BlitRect;
    public int         X, Y, W, H;
};


class AnimatedFrameInfo
{
    public List<SpriteInfo> m_SpriteInfoList    = new List<SpriteInfo>();
    public bool m_bTintScreen                   = false;
    public bool m_bTintCharacter                = false;
    public bool m_bAnimationPartiallyCompleted  = false;
    public int m_iTintScreenRed                 = 0;
    public int m_iTintScreenGreen               = 0;
    public int m_iTintScreenBlue                = 0;
    public int m_iTintScreenAlpha               = 255;
    public int m_iTintCharacterRed              = 0;
    public int m_iTintCharacterGreen            = 0;
    public int m_iTintCharacterBlue             = 0;
    public int m_iWaitTimeTillNextFrame         = 40;
    public string m_sSoundFilename              = "";
};



//===================================
//          Pen and Brush
//===================================
class Pen_and_Brush
{
    private System.Drawing.Pen ThisPen = new System.Drawing.Pen(System.Drawing.Color.Black);
    private System.Drawing.SolidBrush ThisBrush = new System.Drawing.SolidBrush(System.Drawing.Color.Blue);
    private System.Drawing.Graphics ThisGraphics;


    public Pen ClassPen
    {
        get { return ThisPen; }
        set { ThisPen = value; }
    }
    public SolidBrush ClassBrush
    {
        get { return ThisBrush; }
        set { ThisBrush = value; }
    }
    public Graphics ClassGraphics
    {
        get { return ThisGraphics; }
        set { ThisGraphics = value; }
    }
    public Color PenColour
    {
        get { return ThisPen.Color; }
        set { ThisPen.Color = value; }
    }
    public Color BrushColour
    {
        get { return ThisBrush.Color; }
        set { ThisBrush.Color = value; }
    }


    /////////////////////////////////
    public Color HighlightedRectColour
    { get { return Color.Orange; } }

    public Color SelectedRectColour
    { get { return Color.Red; } }
    /////////////////////////////////
};









class ClassXML
{
    List<AnimatedFrameInfo> m_AnimFrameInfoList = new List<AnimatedFrameInfo>();
    bool m_bRelativeToScreen = false;


    //////////////////////////////////////////
    public void WriteToXML(List<AnimatedFrameInfo> AnimFrameInfoList, bool bRelativeToScreen)
    {
        //===========================================
        //          Get Save Location
        //===========================================
        SaveFileDialog SaveFD = new SaveFileDialog();
        SaveFD.Title = "Select a Save Location";
        SaveFD.FileName = "";
        SaveFD.Filter = "XML File (*.xml)|*.xml";
        if (SaveFD.ShowDialog() != System.Windows.Forms.DialogResult.OK) { return; }

        int iPartialCompletionFrame = 0;
        for (; iPartialCompletionFrame < AnimFrameInfoList.Count; iPartialCompletionFrame++)
        {
            if (AnimFrameInfoList.ElementAt(iPartialCompletionFrame).m_bAnimationPartiallyCompleted)
                break;
        }

        System.Xml.XmlTextWriter XmlWriter = new System.Xml.XmlTextWriter(SaveFD.FileName, null);
        XmlWriter.Formatting = System.Xml.Formatting.Indented;

        XmlWriter.WriteStartDocument();
            XmlWriter.WriteStartElement("Animation");
                //===========================================
                //          Write Frame Count
                //===========================================
                XmlWriter.WriteStartElement("AnimationInfo");
                    XmlWriter.WriteStartAttribute("TotalFrames");
                        XmlWriter.WriteString(AnimFrameInfoList.Count.ToString());
                    XmlWriter.WriteEndAttribute();
                    XmlWriter.WriteStartAttribute("PartialAnimationCompletionFrame");
                        XmlWriter.WriteString(iPartialCompletionFrame.ToString());
                    XmlWriter.WriteEndAttribute();
                    XmlWriter.WriteStartAttribute("RelativeToScreen");
                        XmlWriter.WriteString(bRelativeToScreen ? "1" : "0");
                    XmlWriter.WriteEndAttribute();
                XmlWriter.WriteEndElement();
                //===========================================
                //          Write FrameInfo
                //===========================================
                for (int i = 0; i < AnimFrameInfoList.Count(); i++)
                {
                    AnimatedFrameInfo AFI = AnimFrameInfoList.ElementAt(i);
                    ///////////////////////////////////////////////////////
                    XmlWriter.WriteStartElement("Frame" + (i + 1).ToString());
                        XmlWriter.WriteStartAttribute("TotalSprites");
                            XmlWriter.WriteString(AFI.m_SpriteInfoList.Count().ToString());
                        XmlWriter.WriteEndAttribute();
                        XmlWriter.WriteStartAttribute("WaitTillNextFrame");
                            XmlWriter.WriteString(AFI.m_iWaitTimeTillNextFrame.ToString());
                        XmlWriter.WriteEndAttribute();
                        XmlWriter.WriteStartAttribute("TintScreen");
                            XmlWriter.WriteString(AFI.m_bTintScreen ? "1" : "0");
                        XmlWriter.WriteEndAttribute();
                        XmlWriter.WriteStartAttribute("ScreenTintRed");
                            XmlWriter.WriteString(AFI.m_iTintScreenRed.ToString());
                        XmlWriter.WriteEndAttribute();
                        XmlWriter.WriteStartAttribute("ScreenTintGreen");
                            XmlWriter.WriteString(AFI.m_iTintScreenGreen.ToString());
                        XmlWriter.WriteEndAttribute();
                        XmlWriter.WriteStartAttribute("ScreenTintBlue");
                            XmlWriter.WriteString(AFI.m_iTintScreenBlue.ToString());
                        XmlWriter.WriteEndAttribute();
                        XmlWriter.WriteStartAttribute("ScreenTintAlpha");
                            XmlWriter.WriteString(AFI.m_iTintScreenAlpha.ToString());
                        XmlWriter.WriteEndAttribute();
                        XmlWriter.WriteStartAttribute("TintCharacter");
                            XmlWriter.WriteString(AFI.m_bTintCharacter ? "1" : "0");
                        XmlWriter.WriteEndAttribute();
                        XmlWriter.WriteStartAttribute("CharacterTintRed");
                            XmlWriter.WriteString(AFI.m_iTintCharacterRed.ToString());
                        XmlWriter.WriteEndAttribute();
                        XmlWriter.WriteStartAttribute("CharacterTintGreen");
                            XmlWriter.WriteString(AFI.m_iTintCharacterGreen.ToString());
                        XmlWriter.WriteEndAttribute();
                        XmlWriter.WriteStartAttribute("CharacterTintBlue");
                            XmlWriter.WriteString(AFI.m_iTintCharacterBlue.ToString());
                        XmlWriter.WriteEndAttribute();
                        XmlWriter.WriteStartAttribute("SoundFilename");
                            XmlWriter.WriteString(AFI.m_sSoundFilename);
                        XmlWriter.WriteEndAttribute();

                        //===========================================
                        //          Write Sprite Info
                        //===========================================
                        for (int j = 0; j < AFI.m_SpriteInfoList.Count(); j++)
                        {
                            SpriteInfo Sprite = AFI.m_SpriteInfoList.ElementAt(j);
                            //////////////////////////////////////////////////////
                            XmlWriter.WriteStartElement("Sprite" + (j + 1).ToString());
                                XmlWriter.WriteStartAttribute("TextureName");
                                    XmlWriter.WriteString(System.IO.Path.GetFileName(Sprite.TextureName));
                                XmlWriter.WriteEndAttribute();
                                XmlWriter.WriteStartAttribute("X");
                                    XmlWriter.WriteString(Sprite.X.ToString());
                                XmlWriter.WriteEndAttribute();
                                XmlWriter.WriteStartAttribute("Y");
                                    XmlWriter.WriteString(Sprite.Y.ToString());
                                XmlWriter.WriteEndAttribute();
                                XmlWriter.WriteStartAttribute("W");
                                    XmlWriter.WriteString(Sprite.W.ToString());
                                XmlWriter.WriteEndAttribute();
                                XmlWriter.WriteStartAttribute("H");
                                    XmlWriter.WriteString(Sprite.H.ToString());
                                XmlWriter.WriteEndAttribute();
                                ///////////////////////////////////////////////
                                XmlWriter.WriteStartAttribute("UVCoordStartX");
                                    XmlWriter.WriteString(((float)Sprite.BlitRect.X / (float)Sprite.Texture.Width).ToString());
                                XmlWriter.WriteEndAttribute();
                                XmlWriter.WriteStartAttribute("UVCoordStartY");
                                    XmlWriter.WriteString(((float)Sprite.BlitRect.Y / (float)Sprite.Texture.Height).ToString());
                                XmlWriter.WriteEndAttribute();
                                XmlWriter.WriteStartAttribute("UVCoordEndX");
                                    XmlWriter.WriteString((((float)Sprite.BlitRect.X + (float)Sprite.BlitRect.Width) / (float)Sprite.Texture.Width).ToString());
                                XmlWriter.WriteEndAttribute();
                                XmlWriter.WriteStartAttribute("UVCoordEndY");
                                    XmlWriter.WriteString((((float)Sprite.BlitRect.Y + (float)Sprite.BlitRect.Height) / (float)Sprite.Texture.Height).ToString());
                                XmlWriter.WriteEndAttribute();
                            XmlWriter.WriteEndElement();
                        }
                    XmlWriter.WriteEndElement();
                }
            //===========================================
            //          Finish Up
            //===========================================
            XmlWriter.WriteEndElement(); // Animation
        XmlWriter.WriteEndDocument();
        XmlWriter.Close();
    }













    public void ReadFromXML(string sFileName)
    {
        m_AnimFrameInfoList.Clear();
        m_AnimFrameInfoList = new List<AnimatedFrameInfo>();

        int iTotalFrames = 0;
        int iPartialCompletionFrame = 0;
        int iCurrentFrameElement = 1;
        System.Xml.XmlTextReader XmlReader = new System.Xml.XmlTextReader(sFileName);
        System.Xml.XmlNodeType XmlType;


        while (XmlReader.Read())
        {
            XmlReader.ReadAttributeValue();
            XmlType = XmlReader.NodeType;


            if (XmlType == System.Xml.XmlNodeType.Element)
            {
                //===========================================
                //          Get Main Info
                //===========================================
                if (XmlReader.Name == "AnimationInfo")
                {
                    iTotalFrames = Convert.ToInt32(XmlReader.GetAttribute("TotalFrames"));
                    iPartialCompletionFrame = Convert.ToInt32(XmlReader.GetAttribute("PartialAnimationCompletionFrame"));
                    m_bRelativeToScreen = XmlReader.GetAttribute("RelativeToScreen") == "1";
                }

                //===========================================
                //          Get Frame Info
                //===========================================
                if( XmlReader.Name == "Frame" + iCurrentFrameElement.ToString() )
                {
                    AnimatedFrameInfo AFI           = new AnimatedFrameInfo();
                    AFI.m_bTintScreen               = XmlReader.GetAttribute("TintScreen") == "1";
                    AFI.m_iTintScreenRed            = Convert.ToInt32(XmlReader.GetAttribute("ScreenTintRed"));
                    AFI.m_iTintScreenGreen          = Convert.ToInt32(XmlReader.GetAttribute("ScreenTintGreen"));
                    AFI.m_iTintScreenBlue           = Convert.ToInt32(XmlReader.GetAttribute("ScreenTintBlue"));
                    AFI.m_iTintScreenAlpha          = Convert.ToInt32(XmlReader.GetAttribute("ScreenTintAlpha"));

                    AFI.m_bTintCharacter            = XmlReader.GetAttribute("TintCharacter") == "1";
                    AFI.m_iTintCharacterRed         = Convert.ToInt32(XmlReader.GetAttribute("CharacterTintRed"));
                    AFI.m_iTintCharacterGreen       = Convert.ToInt32(XmlReader.GetAttribute("CharacterTintGreen"));
                    AFI.m_iTintCharacterBlue        = Convert.ToInt32(XmlReader.GetAttribute("CharacterTintBlue"));

                    AFI.m_iWaitTimeTillNextFrame    = Convert.ToInt32(XmlReader.GetAttribute("WaitTillNextFrame"));
                    AFI.m_sSoundFilename            = XmlReader.GetAttribute("SoundFilename");

                    int iTotalSprites = Convert.ToInt32(XmlReader.GetAttribute("TotalSprites"));
                    for (int i = 0; i < iTotalSprites;)
                    {
                        XmlReader.Read();
                        if (XmlReader.Name == "Sprite" + (i + 1).ToString())
                        {
                            SpriteInfo SprInfo      = new SpriteInfo();
                            SprInfo.ID              = (uint)AFI.m_SpriteInfoList.Count;
                            SprInfo.TextureName     = XmlReader.GetAttribute("TextureName");
                            SprInfo.X               = Convert.ToInt32(XmlReader.GetAttribute("X"));
                            SprInfo.Y               = Convert.ToInt32(XmlReader.GetAttribute("Y"));
                            SprInfo.W               = Convert.ToInt32(XmlReader.GetAttribute("W"));
                            SprInfo.H               = Convert.ToInt32(XmlReader.GetAttribute("H"));

                            // Multiplying By 1000 Because the Game uses a float value of 0-1, whereas this program uses whole pixels.
                            // Therefore it is saved in game format, but when being read back into this program, the float is multiplied
                            // by 1000 to give an integer pass value, which is corrected by a SpriteChecker function outside of this class.
                            int RectX               = (int)(Convert.ToDouble(XmlReader.GetAttribute("UVCoordStartX")) * 1000.0);
                            int RectY               = (int)(Convert.ToDouble(XmlReader.GetAttribute("UVCoordStartY")) * 1000.0);
                            int RectW               = (int)(Convert.ToDouble(XmlReader.GetAttribute("UVCoordEndX")) * 1000.0);
                            int RectH               = (int)(Convert.ToDouble(XmlReader.GetAttribute("UVCoordEndY")) * 1000.0);
                            SprInfo.BlitRect        = new Rectangle(RectX, RectY, RectW, RectH);

                            AFI.m_SpriteInfoList.Add(SprInfo);
                            i++;
                        }
                    }
                    m_AnimFrameInfoList.Add(AFI);
                    iCurrentFrameElement++;
                }
            }
        }

        //===========================================
        //          Finish Up
        //===========================================
        if ((iPartialCompletionFrame + 1) < m_AnimFrameInfoList.Count)
        {
            m_AnimFrameInfoList.ElementAt(iPartialCompletionFrame - 1).m_bAnimationPartiallyCompleted = true;
        }
        XmlReader.Close();
    }




    public List<AnimatedFrameInfo> GetAnimFrameInfoList() 
    {
        return m_AnimFrameInfoList; 
    }

    public bool GetRelativeToScreen()
    {
        return m_bRelativeToScreen;
    }
};