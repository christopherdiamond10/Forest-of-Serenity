using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;


namespace LevelEditor
{
    public partial class Forest_of_Serenity_LevelEditor : Form
    {


        enum DataState
        {
            // Platforms
            Platform1A,
            Platform1B,
            Platform1C,
            Platform1H,
            Platform1J,
            Platform1K,
            Platform1L,
            Platform1M,
            Log,
            Log1A,
            Log1B,
            Log1C,
            Log2A,
            Log2B,
            Log2C,
            Special1A,
            Special1B,
            Special1C,
            Special1D,
            Platform2A,
            Platform2B,
            Platform2C,
            Platform2D,
            Platform2E,
            Platform2F,
            Platform2G,
            Platform3A,
            Platform3B,
            Platform3C,
            Platform3D,
            Platform3E,
            Platform3F,
            Platform3G,
            Platform3H,
            Platform3I,
            Platform3J,
            Platform3K,
            Platform3L,
            Platform4A,
            Platform4B,
            Platform4C,
            Platform5A,
            Platform5B,
            Platform5C,
            Platform5D,
            Platform5E,
            Platform6A,
            Platform6B,
            Platform7A,
            Platform7B,
            Platform7C,
            Rock,
            Platform8A,
            Platform8B,
            Platform8C,


            // Walls
            Platform1WallA,
            Platform1WallB,
            Platform1WallC,
            Platform1WallD,
            Wood1A,
            Wood1B,
            Wood1C,
            Wood2A,
            Wood2B,
            Wood2C,
            Wood3A,
            Wood3B,
            Wood3C,
            Wood3D,
            Wood4A,
            Wood4B,
            Wood4C,
            Wood4D,
            Wood4E,
            Wood4F,
            Wall2P,
            Wall2Q,
            Wall2R,
            Wall2S,
            Wall2T,
            Wall2K,
            Wall2L,
            Wall2M,
            Wall2N,
            Wall2O,
            Wall2F,
            Wall2G,
            Wall2H,
            Wall2I,
            Wall2J,
            Wall2B,
            Wall2C,
            Wall2D,
            Wall2E,
            Wall2A,
            Wall1F,
            Wall1G,
            Wall1L,
            Wall1C,
            Wall1B,
            Wall1D,
            Wall1I,
            Wall1H,
            Wall1K,
            Wall1J,
            Wall1O,
            Wall1N,
            Wall1M,
            Wall1P,
            Wall1Q,
            Wall1E,
            Wall1A,
            Wall2EdgeL,
            Wall2EdgeK,
            Wall2EdgeF,
            Wall2EdgeG,
            Wall2EdgeH,
            Wall2EdgeI,
            Wall2EdgeJ,
            Wall2EdgeB,
            Wall2EdgeC,
            Wall2EdgeD,
            Wall2EdgeE,
            Wall2EdgeA,
            Wall2X,
            Wall2U,
            Wall2V,
            Wall2W,
            Platform5WallD,
            Platform5WallC,
            Platform5WallB,
            Platform5WallA,
            Platform4WallA,
            Platform4WallB,
            Platform4WallC,


            // Others
            Flower,
            Special1E,
            Special1F,
            Special1G,
            Special1H,
            Special1I,
            Special1J,
            Special1K,
            Special1L,
            Special1M,
            Special1N,
            Statue1A,
            Statue1B,
            Statue1C,
            Statue1D,
            Statue1E,
            Statue1F,
            Statue2A,
            Statue2B,
            Statue2C,
            Statue2D,
            Vines1A,
            Vines1B,
            Vines1C,
            Vines2A,
            Vines2B,
            Vines2C,
            Snowman1A,
            Snowman1B,
            Snowman1C,
            Snowman1D,
            Shading4P,
            Shading4K,
            Shading4L,
            Shading4M,
            Shading4N,
            Shading4O,
            Shading4F,
            Shading4G,
            Shading4H,
            Shading4I,
            Shading4J,
            Shading4E,
            Shading4C,
            Shading4B,
            Shading4A,
            Shading4D,
            Shading3B,
            Shading3C,
            Shading3D,
            Shading3E,
            Shading3F,
            Shading3G,
            Shading3H,
            Shading3I,
            Shading3J,
            Shading3K,
            Shading3A,
            Shading2F,
            Shading2K,
            Shading2M,
            Shading2H,
            Shading2C,
            Shading2E,
            Shading2J,
            Shading2I,
            Shading2D,
            Shading2G,
            Shading2L,
            Shading2B,
            Shading2A,
            Shading1N,
            Shading1M,
            Shading1E,
            Shading1K,
            Shading1B,
            Shading1C,
            Shading1D,
            Shading1G,
            Shading1F,
            Shading1H,
            Shading1I,
            Shading1J,
            Shading1L,
            Shading1A,


            // Events
            PlayerStart,
            Checkpoint1A,
            Star_LevelFinisher,
            Enemy_Bunny,
            Enemy_Snake,
            Enemy_BlueSlime,
            Enemy_GreenSlime,
            Enemy_Imp,
            Enemy_Succubus,
            Green_Crystal,
            Blue_Crystal,
            Red_Crystal,
            Purple_Crystal,
        };



        ////////// Special Panel Buttons //////////
        private void UpdatePanel_Button_Click(object sender, EventArgs e)
        {
            MapPanel.Invalidate();
        }

        private void RemoveTiles_Button_Click(object sender, EventArgs e)
        {
            iActionState = (uint)ActionState.RemoveLevelTile;
        }

        private void RemoveAllTiles_Button_Click(object sender, EventArgs e)
        {
            ClearLevelInfoArray();
            MapPanel.Invalidate();
            AddToRedoUndoList(); // Increment The List
        }





        //==========================================
        //////// Platform Selection Buttons ////////
        //==========================================
        private void Platform1A_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform1A;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform1B_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform1B;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform1C_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform1C;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform1H_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform1H;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform1M_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform1M;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform1J_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform1J;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform1K_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform1K;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform1L_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform1L;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Log1A_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Log1A;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Log1B_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Log1B;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Log1C_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Log1C;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Log_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Log;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Log2A_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Log2A;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Log2B_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Log2B;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Log2C_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Log2C;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Special1A_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Special1A;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Special1B_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Special1B;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Special1C_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Special1C;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Special1D_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Special1D;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform2A_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform2A;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform2B_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform2B;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform2C_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform2C;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform2D_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform2D;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform2E_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform2E;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform2F_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform2F;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform2G_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform2G;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform3A_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform3A;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform3B_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform3B;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform3C_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform3C;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform3D_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform3D;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform3E_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform3E;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform3F_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform3F;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform3G_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform3G;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform3H_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform3H;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform3I_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform3I;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform3J_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform3J;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform3K_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform3K;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform3L_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform3L;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform4A_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform4A;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform4B_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform4B;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform4C_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform4C;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform5A_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform5A;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform5B_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform5B;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform5C_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform5C;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform5D_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform5D;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform5E_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform5E;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform6A_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform6A;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform6B_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform6B;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform7A_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform7A;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform7B_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform7B;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform7C_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform7C;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Rock_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Rock;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform8A_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform8A;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform8B_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform8B;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform8C_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform8C;
            iActionState = (uint)ActionState.AddLevelTile;
        }









        //==========================================
        ////////// Wall Selection Buttons //////////
        //==========================================
        private void Platform1WallA_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform1WallA;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform1WallB_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform1WallB;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform1WallC_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform1WallC;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform1WallD_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform1WallD;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wood1A_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wood1A;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wood1B_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wood1B;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wood1C_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wood1C;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wood2A_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wood2A;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wood2B_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wood2B;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wood2C_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wood2C;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wood3A_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wood3A;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wood3B_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wood3B;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wood3C_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wood3C;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wood3D_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wood3D;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wood4A_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wood4A;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wood4B_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wood4B;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wood4C_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wood4C;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wood4D_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wood4D;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wood4E_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wood4E;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wood4F_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wood4F;
            iActionState = (uint)ActionState.AddLevelTile;
        }
        
        private void Wall2P_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall2P;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall2Q_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall2Q;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall2R_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall2R;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall2S_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall2S;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall2T_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall2T;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall2K_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall2K;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall2L_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall2L;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall2M_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall2M;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall2N_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall2N;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall2O_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall2O;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall2F_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall2F;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall2G_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall2G;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall2H_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall2H;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall2I_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall2I;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall2J_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall2J;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall2B_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall2B;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall2C_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall2C;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall2D_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall2D;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall2E_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall2E;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall2A_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall2A;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall1F_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall1F;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall1G_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall1G;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall1L_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall1L;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall1C_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall1C;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall1B_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall1B;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall1D_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall1D;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall1I_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall1I;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall1H_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall1H;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall1K_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall1K;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall1J_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall1J;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall1O_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall1O;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall1N_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall1N;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall1M_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall1M;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall1P_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall1P;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall1Q_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall1Q;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall1E_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall1E;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall1A_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall1A;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall2EdgeL_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall2EdgeL;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall2EdgeK_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall2EdgeK;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall2EdgeF_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall2EdgeF;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall2EdgeG_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall2EdgeG;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall2EdgeH_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall2EdgeH;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall2EdgeI_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall2EdgeI;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall2EdgeJ_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall2EdgeJ;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall2EdgeB_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall2EdgeB;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall2EdgeC_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall2EdgeC;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall2EdgeD_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall2EdgeD;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall2EdgeE_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall2EdgeE;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall2EdgeA_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall2EdgeA;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall2X_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall2X;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall2U_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall2U;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall2V_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall2V;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Wall2W_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Wall2W;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform5WallD_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform5WallD;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform5WallC_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform5WallC;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform5WallB_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform5WallB;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform5WallA_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform5WallA;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform4WallA_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform4WallA;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Platform4WallB_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform4WallB;
            iActionState = (uint)ActionState.AddLevelTile;

        }

        private void Platform4WallC_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Platform4WallC;
            iActionState = (uint)ActionState.AddLevelTile;
        }










        //==========================================
        ///////// Others Selection Buttons /////////
        //==========================================
        private void Flower_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Flower;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Special1E_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Special1E;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Special1F_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Special1F;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Special1G_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Special1G;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Special1H_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Special1H;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Special1I_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Special1I;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Special1J_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Special1J;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Special1K_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Special1K;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Special1L_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Special1L;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Special1M_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Special1M;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Special1N_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Special1N;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Statue1A_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Statue1A;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Statue1B_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Statue1B;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Statue1C_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Statue1C;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Statue1D_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Statue1D;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Statue1E_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Statue1E;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Statue1F_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Statue1F;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Statue2A_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Statue2A;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Statue2B_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Statue2B;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Statue2C_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Statue2C;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Statue2D_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Statue2D;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Vines1A_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Vines1A;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Vines1B_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Vines1B;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Vines1C_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Vines1C;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Vines2A_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Vines2A;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Vines2B_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Vines2B;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Vines2C_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Vines2C;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Snowman1A_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Snowman1A;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Snowman1B_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Snowman1B;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Snowman1C_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Snowman1C;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Snowman1D_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Snowman1D;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading4P_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading4P;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading4K_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading4K;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading4L_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading4L;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading4M_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading4M;
            iActionState = (uint)ActionState.AddLevelTile;

        }

        private void Shading4N_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading4N;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading4O_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading4O;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading4F_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading4F;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading4G_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading4G;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading4H_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading4H;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading4I_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading4I;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading4J_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading4J;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading4E_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading4E;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading4C_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading4C;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading4B_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading4B;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading4A_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading4A;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading4D_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading4D;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading3B_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading3B;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading3C_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading3C;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading3D_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading3D;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading3E_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading3E;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading3F_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading3F;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading3G_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading3G;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading3H_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading3H;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading3I_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading3I;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading3J_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading3J;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading3K_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading3K;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading3A_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading3A;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading2F_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading2F;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading2K_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading2K;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading2M_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading2M;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading2H_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading2H;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading2C_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading2C;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading2E_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading2E;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading2J_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading2J;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading2I_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading2I;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading2D_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading2D;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading2G_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading2G;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading2L_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading2L;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading2B_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading2B;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading2A_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading2A;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading1N_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading1N;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading1M_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading1M;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading1E_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading1E;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading1K_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading1K;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading1B_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading1B;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading1C_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading1C;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading1D_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading1D;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading1G_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading1G;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading1F_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading1F;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading1H_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading1H;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading1I_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading1I;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading1J_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading1J;
            iActionState = (uint)ActionState.AddLevelTile;

        }

        private void Shading1L_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading1L;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Shading1A_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Shading1A;
            iActionState = (uint)ActionState.AddLevelTile;
        }




        //==========================================
        ///////// Events Selection Buttons /////////
        //==========================================
        private void PlayerStart_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.PlayerStart;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Checkpoint1A_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Checkpoint1A;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Star_LevelFinisher_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Star_LevelFinisher;
            iActionState = (uint)ActionState.AddLevelTile;
        }


        private void Enemy_Bunny_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Enemy_Bunny;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Enemy_Snake_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Enemy_Snake;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Enemy_BlueSlime_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Enemy_BlueSlime;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Enemy_GreenSlime_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Enemy_GreenSlime;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Enemy_Imp_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Enemy_Imp;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Enemy_Succubus_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Enemy_Succubus;
            iActionState = (uint)ActionState.AddLevelTile;
        }


        private void Green_Crystal_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Green_Crystal;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Blue_Crystal_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Blue_Crystal;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Red_Crystal_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Red_Crystal;
            iActionState = (uint)ActionState.AddLevelTile;
        }

        private void Purple_Crystal_Button_Click(object sender, EventArgs e)
        {
            iDataState = (uint)DataState.Purple_Crystal;
            iActionState = (uint)ActionState.AddLevelTile;
        }
    }
}
