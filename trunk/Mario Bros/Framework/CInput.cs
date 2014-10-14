using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Input;

namespace Mario_Bros.Framework
{
    public class CInput
    {
        private KeyboardState m_CurKey;
        private KeyboardState m_OldKey;

        public KeyboardState CurKey
        {
            get { return m_CurKey; }
            set { m_CurKey = value; }
        }

        public KeyboardState OldKey
        {
            get { return m_OldKey; }
            set { m_OldKey = value; }
        }

        public CInput()
        {
            m_CurKey = Keyboard.GetState();
        }

        public void Update()
        {
            m_OldKey = m_CurKey;
            m_CurKey = Keyboard.GetState();
        }

        public bool KeyReleased(Keys _Key)
        {
            return m_CurKey.IsKeyUp(_Key) && m_OldKey.IsKeyDown(_Key);
        }

        public bool KeyPressed(Keys _Key)
        {
            return m_CurKey.IsKeyDown(_Key) && m_OldKey.IsKeyUp(_Key);
        }

        public bool KeyDown(Keys _Key)
        {
            return m_CurKey.IsKeyDown(_Key);
        }
    }
}
