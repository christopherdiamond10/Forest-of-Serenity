using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;




//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//          Structs
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
struct TexturesInfo
{
    public string TextureName;
    public string PathToTexture;
    public Image Texture;
};

struct WeatherInfo
{
    public string Type;
    public uint X, Y, W, H;
    public Image Texture;
};

struct RedoUndoInfo
{
    public string AudioName;
    public string BackgroundImageName;
    public string FullPathToImage;
    public string AudioInfoTextBoxText;
    public int AudioLoopStart_NumericUpDownValue;
    public int AudioLoopEnd_NumericUpDownValue;
    public List<List<LevelInfo>> lLevelDataList;
    public List<WeatherInfo> lWeatherEffectOne;
    public List<WeatherInfo> lWeatherEffectTwo;
     
    public int WeatherEffect1_ComboBoxSelectedIndex;
    public int WeatherEffect2_ComboBoxSelectedIndex;
    public int WeatherEffectOnePower_NumericUpDownValue;
    public int WeatherEffectTwoPower_NumericUpDownValue;
     
    public int TileRows_NumericUpDownValue;
    public int TileCols_NumericUpDownValue;
};

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//          Enums
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//===================================
//         Action States
//===================================
enum ActionState
{
    AddLevelTile,
    RemoveLevelTile
};
//===================================
//         Tab States
//===================================
enum TabState
{
    Platforms,
    Walls,
    Others,
    Events
};
//===================================
//         Data States
//===================================





//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//          Classes
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//===================================
//         Level Info Array
//===================================
class LevelInfo
{
    public string TextureName = null;
    public Image Texture = null;
    public uint X, Y, W, H;
};
//===================================
//         Mouse Action
//===================================
class MousePos
{
    public float X, Y;
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
    public Color NormalWaypointColour
    { get { return Color.Blue; } }

    public Color HighlightedWaypointColour
    { get { return Color.Orange; } }

    public Color SelectedWaypointColour
    { get { return Color.Red; } }

    public Color ConnectionColour
    { get { return Color.LightYellow; } }

    public Color GridLinesColour
    { get { return Color.Black; } }
    /////////////////////////////////
};

//===================================
//            Map Grid
//===================================
class MapGrid
{
    // Variables
    private const int m_iTileSize = 32;

    private int m_iTileRows = 24;
    private int m_iTileCols = 32;


    // Functions
    public int TileSizeValue
    { get { return m_iTileSize; } }

    public int TileRowsValue
    {
        get { return m_iTileRows; }
        set { m_iTileRows = value; }
    }

    public int TileColsValue
    {
        get { return m_iTileCols; }
        set { m_iTileCols = value; }
    }
};





class MapXML
{
    bool m_bWarnedAboutNeedingToImportTextureAndSound = false;

    string m_sFullPathToBackgroundImage;
    string m_sBackgroundImageName;
    string m_sAudioName;
    string m_sAudioLoopStart;
    string m_sAudioLoopEnd;
    string m_sWeatherEffectOne;
    string m_sPowerOfWeatherEffectOne;
    string m_sWeatherEffectTwo;
    string m_sPowerOfWeatherEffectTwo;
    string m_sTileRows;
    string m_sTileCols;

    List<List<LevelInfo>> m_lLevelInfoList;


    
    //////////////////////////////////////////
    public void WriteToXML(string sFullImagePath, string sMapImageFileName, string sAudioFileName, uint iAudioLoopStart, uint iAudioLoopEnd, string sWeatherEffectOne, uint iPowerOfWeatherEffectOne, string sWeatherEffectTwo, uint iPowerOfWeatherEffectTwo, List<List<LevelInfo>> lLevelInfoList, uint iTileRows, uint iTileCols )
    {
        if (sMapImageFileName == null && sAudioFileName == null)
        {
            string sWarning = "WARNING, You do not have either a background image or audio for this level (what the hell do you think this is?), would you like to continue?";
            if (MessageBox.Show(sWarning, "Warning!", MessageBoxButtons.YesNo) != DialogResult.Yes) { return; }
        }
        else if (sMapImageFileName == null)
        {
            string sWarning = "WARNING, You do not have a background image for this level, are you sure you want a regular boring background for this level?";
            if (MessageBox.Show(sWarning, "Warning!", MessageBoxButtons.YesNo) != DialogResult.Yes) { return; }
        }
        else if (sAudioFileName == null)
        {
            string sWarning = "WARNING, You do not have audio selected for this level, are you sure you don't want to allow the level to seduce your ears?";
            if (MessageBox.Show(sWarning, "Warning!", MessageBoxButtons.YesNo) != DialogResult.Yes) { return; }
        }
        //===========================================
        //          Get Save Location
        //===========================================
        SaveFileDialog SaveFD = new SaveFileDialog();
        SaveFD.Title = "Select a Save Location";
        SaveFD.FileName = "";
        SaveFD.Filter = "XML File (*.xml)|*.xml";
        if (SaveFD.ShowDialog() != System.Windows.Forms.DialogResult.OK)
        { return; }

        
        System.Xml.XmlTextWriter XmlWriter = new System.Xml.XmlTextWriter(SaveFD.FileName, null);
        XmlWriter.Formatting = System.Xml.Formatting.Indented;

        XmlWriter.WriteStartDocument();
            XmlWriter.WriteStartElement("LevelInfo");
                //===========================================
                //          Write Level Size
                //===========================================
                XmlWriter.WriteStartElement("LevelSize");
                    XmlWriter.WriteStartAttribute("Rows");
                        XmlWriter.WriteString(iTileRows.ToString());
                    XmlWriter.WriteEndAttribute();
                    XmlWriter.WriteStartAttribute("Cols");
                        XmlWriter.WriteString(iTileCols.ToString());
                    XmlWriter.WriteEndAttribute();
                XmlWriter.WriteEndElement();
                //===========================================
                //          Write LevelData
                //===========================================
                XmlWriter.WriteStartElement("LevelData");
                    for (int Row = 0; Row < lLevelInfoList.Count(); Row++)
                    {
                        XmlWriter.WriteStartElement("Row");
                        for (int Col = 0; Col < lLevelInfoList.ElementAt(Row).Count(); Col++)
                        {
                            int iIncrem = Col + 1;
                            XmlWriter.WriteStartAttribute("Col" + iIncrem.ToString());
                                XmlWriter.WriteString(lLevelInfoList.ElementAt(Row).ElementAt(Col).TextureName);
                            XmlWriter.WriteEndAttribute();
                        }
                        XmlWriter.WriteEndElement();
                    }
                XmlWriter.WriteEndElement();
                //===========================================
                //          Write Background Texture
                //===========================================
                XmlWriter.WriteStartElement("BackgroundImage");
                    XmlWriter.WriteStartAttribute("Name");
                        XmlWriter.WriteString(sMapImageFileName);
                    XmlWriter.WriteEndAttribute();
                    XmlWriter.WriteStartAttribute("FullPath");
                        XmlWriter.WriteString(sFullImagePath);
                    XmlWriter.WriteEndAttribute();
                XmlWriter.WriteEndElement();
                //===========================================
                //          Write Audio Info
                //===========================================
                XmlWriter.WriteStartElement("AudioName");
                    XmlWriter.WriteStartAttribute("Name");
                        XmlWriter.WriteString(sAudioFileName);
                    XmlWriter.WriteEndAttribute();
                    XmlWriter.WriteStartAttribute("LoopStart");
                        XmlWriter.WriteString(iAudioLoopStart.ToString());
                    XmlWriter.WriteEndAttribute();
                    XmlWriter.WriteStartAttribute("LoopEnd");
                        XmlWriter.WriteString(iAudioLoopEnd.ToString());
                    XmlWriter.WriteEndAttribute();
                XmlWriter.WriteEndElement(); 
                //===========================================
                //          Write NoteTag Info
                //===========================================
                XmlWriter.WriteStartElement("Weather");
                    XmlWriter.WriteStartElement("EffectOne");
                        XmlWriter.WriteStartAttribute("Type");
                            XmlWriter.WriteString(sWeatherEffectOne);
                        XmlWriter.WriteEndAttribute();
                        XmlWriter.WriteStartAttribute("Power");
                            XmlWriter.WriteString(iPowerOfWeatherEffectOne.ToString());
                        XmlWriter.WriteEndAttribute();
                    XmlWriter.WriteEndElement();
                    XmlWriter.WriteStartElement("EffectTwo");
                        XmlWriter.WriteStartAttribute("Type");
                            XmlWriter.WriteString(sWeatherEffectTwo);
                        XmlWriter.WriteEndAttribute();
                        XmlWriter.WriteStartAttribute("Power");
                            XmlWriter.WriteString(iPowerOfWeatherEffectTwo.ToString());
                        XmlWriter.WriteEndAttribute();
                    XmlWriter.WriteEndElement();
                XmlWriter.WriteEndElement();
            //===========================================
            //          Finish Up
            //===========================================
            XmlWriter.WriteEndElement(); // LevelInfo
        XmlWriter.WriteEndDocument();
        XmlWriter.Close();


        if ((!m_bWarnedAboutNeedingToImportTextureAndSound && sMapImageFileName != null) || (!m_bWarnedAboutNeedingToImportTextureAndSound && sAudioFileName != null))
        {
            m_bWarnedAboutNeedingToImportTextureAndSound = true;
            MessageBox.Show("Note that whilst you have successfully saved an XML File, you will not be able to use your custom texture or sound unless you import it to the appropriate game folder");
        }
    }






    






    public void ReadFromXML(string sFileName)
    {
        m_lLevelInfoList = new List<List<LevelInfo>>();
        

        System.Xml.XmlTextReader XmlReader = new System.Xml.XmlTextReader(sFileName);
        System.Xml.XmlNodeType XmlType;
        

        while (XmlReader.Read())
        {
            XmlReader.ReadAttributeValue();
            XmlType = XmlReader.NodeType;


            if (XmlType == System.Xml.XmlNodeType.Element)
            {
                //===========================================
                //          Get LevelSize Info
                //===========================================
                if (XmlReader.Name == "LevelSize")
                {
                    m_sTileRows = XmlReader.GetAttribute("Rows");
                    m_sTileCols = XmlReader.GetAttribute("Cols");
                }

                //===========================================
                //          Get Array Info
                //===========================================
                else if (XmlReader.Name == "Row")
                {
                    int ColAmount = Convert.ToInt32(m_sTileCols);
                    List<LevelInfo> LevInfoList = new List<LevelInfo>();
                    for (int i = 0; i < ColAmount; i++)
                    {
                        LevelInfo LevInfo = new LevelInfo(); int CurrentCol = i + 1;
                        LevInfo.X = (uint)i * 32; LevInfo.Y = (uint)m_lLevelInfoList.Count() * 32; LevInfo.W = 32; LevInfo.H = 32;
                        LevInfo.TextureName = XmlReader.GetAttribute("Col" + CurrentCol.ToString());
                        LevInfoList.Add(LevInfo);
                    }
                    m_lLevelInfoList.Add(LevInfoList);
                }

                //===========================================
                //         Get Background Image Info
                //===========================================
                else if (XmlReader.Name == "BackgroundImage")
                {
                    m_sBackgroundImageName = XmlReader.GetAttribute("Name");
                    m_sFullPathToBackgroundImage = XmlReader.GetAttribute("FullPath");
                }

                //===========================================
                //          Get Audio Info
                //===========================================
                else if (XmlReader.Name == "AudioName")
                {
                    m_sAudioName = XmlReader.GetAttribute("Name");
                    m_sAudioLoopStart = XmlReader.GetAttribute("LoopStart");
                    m_sAudioLoopEnd = XmlReader.GetAttribute("LoopEnd");
                }
                //===========================================
                //          Get Weather Info
                //===========================================
                else if (XmlReader.Name == "EffectOne")
                {
                    m_sWeatherEffectOne = XmlReader.GetAttribute("Type");
                    m_sPowerOfWeatherEffectOne = XmlReader.GetAttribute("Power");
                }
                else if (XmlReader.Name == "EffectTwo")
                {
                    m_sWeatherEffectTwo = XmlReader.GetAttribute("Type");
                    m_sPowerOfWeatherEffectTwo = XmlReader.GetAttribute("Power");
                }
            }
        }

        //===========================================
        //          Finish Up
        //===========================================
        XmlReader.Close();
    }






    public void SetClassXmlToNull()
    {
        m_sBackgroundImageName      = null;
        m_sAudioName                = null;
        m_sAudioLoopStart           = null;
        m_sAudioLoopEnd             = null;
        m_sWeatherEffectOne         = null;
        m_sPowerOfWeatherEffectOne  = null;
        m_sWeatherEffectTwo         = null;
        m_sPowerOfWeatherEffectTwo  = null;
        m_sTileRows                 = null;
        m_sTileCols                 = null;
        m_lLevelInfoList.Clear();
    }


    public List<List<LevelInfo>> GetLevelList()     { return m_lLevelInfoList; }
    public string GetTileRows()                     { return m_sTileRows; }
    public string GetTileCols()                     { return m_sTileCols; }
    public string GetFullPathToBackgroundImage()    { return m_sFullPathToBackgroundImage; }
    public string GetBackgroundImageName()          { return m_sBackgroundImageName; }
    public string GetAudioName()                    { return m_sAudioName; }
    public string GetAudioLoopStart()               { return m_sAudioLoopStart; }
    public string GetAudioLoopEnd()                 { return m_sAudioLoopEnd;  }
    public string GetWeatherEffectOneType()         { return m_sWeatherEffectOne; }
    public string GetWeatherEffectOnePower()        { return m_sPowerOfWeatherEffectOne; }
    public string GetWeatherEffectTwoType()         { return m_sWeatherEffectTwo; }
    public string GetWeatherEffectTwoPower()        { return m_sPowerOfWeatherEffectTwo; }
};